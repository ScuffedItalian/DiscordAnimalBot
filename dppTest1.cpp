#include <fstream>
#include <iostream>
#include <string>
#include "dpp/dpp.h"
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using namespace std;
using json = nlohmann::json;

void greeting()
{
    cout << "Hello!" << endl;
    cout << "Thank you for using my bot template" << endl;
    cout << "This template was developed by ScuffedItalian#5158" << endl;
    cout << "If you need any support, you may look on the github page" << endl;
}



int main(int argc, char* argv[])
{
    
    std::ifstream file("token.json");
    std::string file_contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    json config = json::parse(file_contents);
    std::string token = config["token"];
    greeting();
    cout << "Your token is: " + token << endl;
    
    dpp::cluster bot(token);
    bot.on_log(dpp::utility::cout_logger());
    
    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        

        if(event.command.get_command_name() == "catpicture")
        {
           auto response = cpr::Get(cpr::Url{"https://api.thecatapi.com/v1/images/search"});

            auto json = nlohmann::json::parse(response.text);
            std::string image_url = json[0]["url"];

            event.reply(dpp::message(image_url));
        }
        if (event.command.get_command_name() == "dogpicture")
        {
            auto response = cpr::Get(cpr::Url{"https://dog.ceo/api/breeds/image/random"});

            auto json = nlohmann::json::parse(response.text);
            std::string image_url = json["message"];

            event.reply(dpp::message(image_url));
        }
        if (event.command.get_command_name() == "redpandapicture")
        {
            auto response = cpr::Get(cpr::Url{"https://some-random-api.ml/animal/red_panda"});
            auto json = nlohmann::json::parse(response.text);
            std::string image_url = json["image"];

            event.reply(dpp::message(image_url));
        }
        if (event.command.get_command_name() == "birdpicture")
        {
            auto response = cpr::Get(cpr::Url{"https://some-random-api.ml/animal/bird"});
            auto json = nlohmann::json::parse(response.text);
            std::string image_url = json["image"];

            event.reply(dpp::message(image_url));
        }
        if(event.command.get_command_name() == "koalapicture")
        {
            auto response = cpr::Get(cpr::Url{"https://some-random-api.ml/animal/koala"});
            auto json = nlohmann::json::parse(response.text);
            std::string image_url = json["image"];

            event.reply(dpp::message(image_url));
        }
        if(event.command.get_command_name() == "help")
        {
            event.reply("This is a list of commands: \n /ping \n /catpicture \n /dogpicture \n /redpandapicture \n /birdpicture \n /koalapicture");
        }

    });
    
    bot.on_ready([&bot](const dpp::ready_t& event) {
       if (dpp::run_once<struct register_bot_commands>()) {
          
           bot.global_command_create(
                dpp::slashcommand("catpicture", "Get a random cat picture", bot.me.id)
            
           );
           bot.global_command_create(
               dpp::slashcommand("dogpicture", "Get a random dog picture", bot.me.id)
           );
           bot.global_command_create(
                dpp::slashcommand("redpandapicture", "Get a random red panda picture", bot.me.id)
           );
           bot.global_command_create(
                dpp::slashcommand("birdpicture", "Get a random bird picture", bot.me.id)  
           );
           bot.global_command_create(
                dpp::slashcommand("koalapicture", "Get a random koala picture", bot.me.id)
           );
           bot.global_command_create(
                dpp::slashcommand("help", "Get a list of commands", bot.me.id)
           );
       }
   });
    
    bot.start(false);
    std::cout << "Hello World";
    return 0;
}
