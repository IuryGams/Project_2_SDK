#include "energy_meter_services.hpp"
#include "operations.hpp"
#include "energy_meter.hpp"
#include "enums.hpp"
#include "utils.hpp"

#include <vector>
#include <string>

namespace energy
{
    ees::Operations operations;

    grpc::Status EnergyMeterServiceImpl::CreateMeter(grpc::ServerContext *context, const MeterInfor *request, MeterCompleteInfor *reply)
    {
        ees::EnergyMeter new_meter(static_cast<ees::Lines>(request->line()), request->model());

        if (operations.add_new_model(new_meter))
        {
            reply->set_id(new_meter.get_id());
            reply->set_line(static_cast<Lines>(new_meter.get_line()));
            reply->set_model(new_meter.get_model());
            return grpc::Status::OK;
        }
        else
        {
            std::cout << "O medidor já existe e não foi adicionado." << std::endl;
            return grpc::Status(grpc::ALREADY_EXISTS, "Medidor já existe");
        }
    }

    grpc::Status EnergyMeterServiceImpl::ReadMeter(grpc::ServerContext *context, const MeterID *request, MeterCompleteInfor *reply)
    {
        try
        {
            // Encontra o medidor pelo ID
            ees::EnergyMeter found_meter = operations.find_meter_by_id(request->id());

            // Preenche os dados do medidor no reply
            reply->set_id(found_meter.get_id());
            reply->set_line(static_cast<Lines>(found_meter.get_line()));
            reply->set_model(found_meter.get_model());

            return grpc::Status::OK;
        }
        catch (const std::runtime_error &e)
        {
            // Caso o medidor não seja encontrado, retorna um status NOT_FOUND com mensagem apropriada
            return grpc::Status(grpc::StatusCode::NOT_FOUND, e.what());
        }
    }

    grpc::Status EnergyMeterServiceImpl::GetAllMeters(grpc::ServerContext *context, const Empty *request, MeterListRequest *reply)
    {
        try
        {
            std::cout << "Solicitado a lista de medidores" << std::endl;

            std::vector<ees::EnergyMeter> list_meters = operations.get_meter_list();
            std::cout << "Número de medidores recebidos: " << list_meters.size() << std::endl;

            for (const auto &meter : list_meters)
            {
                // std::cout << "ID do medidor: " << meter.get_id() << std::endl;
                // std::cout << "Linha do medidor: " << ees::convert_enumline_to_string(meter.get_line()) << std::endl;
                // std::cout << "Modelo do medidor: " << meter.get_model() << std::endl;

                MeterCompleteInfor *meter_info = reply->add_meters();
                meter_info->set_id(meter.get_id());
                meter_info->set_line(static_cast<::Lines>(convert_to_proto_enum(meter.get_line())));
                meter_info->set_model(meter.get_model());
            }

            return grpc::Status::OK;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Erro ao obter a lista de medidores: " << e.what() << std::endl;
            return grpc::Status(grpc::StatusCode::INTERNAL, "Erro interno ao obter a lista de medidores");
        }
    }

    grpc::Status EnergyMeterServiceImpl::DeleteMeter(grpc::ServerContext *context, const MeterID *request, ResponseStatus *reply)
    {
        if (operations.remove_model(request->id()))
        {
            reply->set_status(ResponseStatus::COMMAND_EXECUTION_SUCCESSFUL);
            return grpc::Status::OK;
        }
        reply->set_status(ResponseStatus::COMMAND_EXECUTION_FAILED);

        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::GetAllLines(grpc::ServerContext *context, const Empty *request, AllLinesRequest *reply)
    {

        // Limpa qualquer dado pré-existente em reply
        reply->clear_lines();

        // Adiciona todas as linhas disponíveis de acordo com o enum Lines
        reply->add_lines(Lines::ARES);
        reply->add_lines(Lines::APOLO);
        reply->add_lines(Lines::CRONOS);
        reply->add_lines(Lines::ZEUS);

        // Retorna Status OK para indicar sucesso na operação
        return grpc::Status::OK;
    }

    grpc::Status EnergyMeterServiceImpl::GetModelsByLine(grpc::ServerContext *context, const MeterLine *request, MeterListRequest *reply)
    {
        std::string line = request->meter_line();

        auto models = operations.filter_by_line(ees::to_uppercase(line));

        for (const auto &model : models)
        {
            std::cout << "ID do medidor: " << model.get_id() << std::endl;
            std::cout << "Linha do medidor: " << ees::convert_enumline_to_string(model.get_line()) << std::endl;
            std::cout << "Modelo do medidor: " << model.get_model() << std::endl;


            auto *meter_infor = reply->add_meters();
            meter_infor->set_id(model.get_id());
            meter_infor->set_line(static_cast<Lines>(model.get_line()));
            meter_infor->set_model(model.get_model());
        }

        return grpc::Status::OK;
    }

}

