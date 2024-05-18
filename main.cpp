#include "roblox/classes/classes.hpp"
#include "utils/configs/configs.hpp"

#include <filesystem>
#include <iostream>
#include <thread>

#include "keyauth/auth.hpp"
#include <string>
#include "keyauth/utils.hpp"
#include "keyauth/skStr.h"

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);
const std::string compilation_date = (std::string)skCrypt(__DATE__);
const std::string compilation_time = (std::string)skCrypt(__TIME__);

using namespace KeyAuth;

auto name = skCrypt("Ethic");
auto ownerid = skCrypt("4dHMq5vtSq");
auto secret = skCrypt("7fd66e8e81c1e09a942490b5e910cb2055050f9413646d7b8b3d4645f3b2dbfe");
auto version = skCrypt("1.0");
auto url = skCrypt("https://keyauth.win/api/1.2/"); // change if you're self-hosting

api KeyAuthApp(name.decrypt(), ownerid.decrypt(), secret.decrypt(), version.decrypt(), url.decrypt());

int main(/* credits to AGC / A GREAT CHAOS / KEN CARSON / mogus (lua env) */)
{
    name.clear(); ownerid.clear(); secret.clear(); version.clear(); url.clear();
    
    std::string consoleTitle = skCrypt("Silence").decrypt();
    SetConsoleTitleA(consoleTitle.c_str());
    // system("Color 0C");
    KeyAuthApp.init();
    if (!KeyAuthApp.data.success)
    {
        std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
        Sleep(1500);
        exit(1);
    }

    if (std::filesystem::exists("silence.json"))
    {
        if (!CheckIfJsonKeyExists("silence.json", "username"))
        {
            std::string key = ReadFromJson("silence.json", "license");
            KeyAuthApp.license(key);
            if (!KeyAuthApp.data.success)
            {
                std::remove("silence.json");
                std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
                Sleep(1500);
                exit(1);
            }
            std::cout << skCrypt("silence > auto logged in\n");
        }
        else
        {
            std::string username = ReadFromJson("silence.json", "username");
            std::string password = ReadFromJson("silence.json", "password");
            KeyAuthApp.login(username, password);
            if (!KeyAuthApp.data.success)
            {
                std::remove("silence.json");
                std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
                Sleep(1500);
                exit(1);
            }
            std::cout << skCrypt("silence > auto logged in\n");
        }
    }
    else
    {
        int option;
        std::string username;
        std::string password;
        std::string key;

        std::cout << skCrypt("silence > license key -> ");
        std::cin >> key;
        KeyAuthApp.license(key);

        if (!KeyAuthApp.data.success)
        {
            std::cout << skCrypt("\n Status: ") << KeyAuthApp.data.message;
            Sleep(1500);
            exit(1);
        }
        if (username.empty() || password.empty())
        {
            WriteToJson("silence.json", "license", key, false, "", "");
            std::cout << skCrypt("silence > created file for auto-login\n");
        }
        else
        {
            WriteToJson("silence.json", "username", username, true, "password", password);
            std::cout << skCrypt("silence > created file for auto-login\n");
        }
    }

    std::string appdata = silence::utils::appdata_path();
    if (!std::filesystem::exists(appdata + "\\silence"))
    {
        std::filesystem::create_directory(appdata + "\\silence");
    }

    if (!std::filesystem::exists(appdata + "\\silence\\configs"))
    {
        std::filesystem::create_directory(appdata + "\\silence\\configs");

    }

    silence::roblox::init();

    printf("silence > press enter to close console [closes cheat]");
    std::cin.get();

    //system("pause");
}