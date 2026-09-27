#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream> 

int load(std::string *API_key,std::string *content){
	const std::string batContent =
        "@echo off\n"
        "chcp 65001 >nul\n"
        "set API_KEY=" + *API_key + "\n"
        "set QUESTION=" + *content + "\n"
        "\n"
        "curl -X POST \"https://api.deepseek.com/chat/completions\" ^\n"
        "  -H \"Content-Type: application/json\" ^\n"
        "  -H \"Authorization: Bearer %API_KEY%\" ^\n"
        "  -d \"{\\\"model\\\": \\\"deepseek-flash\\\", \\\"messages\\\": [{\\\"role\\\": \\\"user\\\", \\\"content\\\": \\\"%QUESTION%\\\"}], \\\"stream\\\": false}\"\n"
        "pause\n";
        
            std::ofstream outFile("ask.bat", std::ios::out | std::ios::binary);
    if (!outFile) { std::cerr << "cannot create ask.bat\n"; return 1; }
    outFile << batContent;
    outFile.close();

    std::cout << "ask.bat generated with question: " << *content << "\n";
    return 0;
}



int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cout << "usage: dpsk --help | --model <name>\n";
        return 1;
    }

    std::string arg1 = argv[1];

    if (arg1 == "--help" || arg1 == "-h") {
        std::cout << "--model [model_name]   to select a model\n";
        std::cout << "-m [model_name]        short form\n";
        return 0;
    }
    else if (arg1 == "--model" || arg1 == "-m") {
        if (argc < 3) {
            std::cout << "Error: --model needs a model name\n";
            return 1;
        }
        std::string model = argv[2];

        if (model == "deepseek-flash") {
            std::cout << "model set to deepseek-flash\n";
            if(argc<4){
            	return 0;
			}
			std::string content = argv[3];
			if(content == "--content" || content == "-c"){
				if(argc < 5){
				std::cout << "argument missing" << "\n";	
				return 1;
				}
				
				std::string API_key = "sk-f8542f73f8c3403ca8855e0353c3f051";
				std::string content_arg = argv[4]; 

				if(load(&API_key, &content_arg) == 0){
					std::cout << "Succeeded!"<<"\n";
					system("ask.bat");
				}else{
					std::cout<< "Failed"<<"\n";
					return 1;
				}
				
				return 0;
			}

        }
        else if (model == "deepseek-chat") {
            std::cout << "model set to deepseek-chat\n";
        }
        else {
            std::cout << "unknown model: " << model << "\n";
            return 1;
        }
        return 0;
    }

    std::cout << "invalid argument: " << arg1 << "\n";
    return 1;
}
