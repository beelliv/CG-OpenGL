#include "Screenshot.h"
#include <iostream>
#include <filesystem>


#include <sstream>
#include <iomanip>
#include <algorithm>
#include <regex>
#include <SOIL2/SOIL2.h>


using namespace std;


namespace fs = std::filesystem;

Screenshot::Screenshot(){

}


bool Screenshot::saveScreenshot(int winWidth, int winHeight){

    fs::path screenshotPath = fs::current_path().parent_path();
    screenshotPath.append("screenshot");

    //cout << screenshotPath << endl;
    

    if(!fs::exists(screenshotPath))
        fs::create_directory(screenshotPath);

    int count = 0;
    for (const auto & entry : fs::directory_iterator(screenshotPath)){
        if(entry.path().has_filename())
        {
            //string input =  entry.path().filename().string();
            string input =  entry.path().stem().string(); //sem a extenção
            //cout << input << endl;

            if(input.rfind("screenshot_", 0) == 0)
            {
                std::string output;
                std::smatch match;
                std::regex_search(input, match, std::regex("([1-9])([0-9]*)"));
                
                if(match.size()>0){
                    int n = std::stoi( match.str(0) );
                    //cout << n << endl;
                    if(n> count)
                        count = n;
                }

            }
            
        }
    }
    count++; //incrementa o contador de screenshot


    std::ostringstream ss;
    ss << std::setw(3) << std::setfill('0') << count;

    screenshotPath.append("screenshot_" + ss.str() + ".png");
    
    //cout << screenshotPath.string() << endl;

    if( ! SOIL_save_screenshot( screenshotPath.string().c_str(), SOIL_SAVE_TYPE_PNG, 0, 0, winWidth, winHeight) )
    {
        cout << "Erro Screenshot: erro ao salvar o arquivo com SOIL!\n";
        return false;
    }

    cout << "\nScreenshot: " << screenshotPath << endl;



    return true;
}
