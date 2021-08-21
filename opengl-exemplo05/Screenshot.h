#ifndef SCREENSHOT_H_INCLUDED
#define SCREENSHOT_H_INCLUDED

#include <string>

class Screenshot
{
public:
    Screenshot();

    //salva um screenshot na pasta "../screenshot", ou seja, "projetoCG/screenshot"
    //A numeracao dos arquivos é definida a partir do último screenshot realizado, nomeando o arquivo como screenshot_001.png, screenshot_002.png, ...
    //Arquivos previamente capturados são preservados
    static bool saveScreenshot(int winWidth, int winHeight);

};

#endif