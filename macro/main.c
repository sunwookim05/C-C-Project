#include <windows.h> 
#include <stdio.h>

#define delay Sleep(1)
#define kM keyprint(0x4d)
#define down keyprint(VK_DOWN)
#define up keyprint(VK_UP)
#define right keyprint(VK_RIGHT)
#define left keyprint(VK_LEFT)
#define Enter keyprint(VK_RETURN)

int ceo = 0;

void playUI();

typedef void (*pfn_FooBar)();

void processMemory(){
    HRSRC hResInfo = FindResource (NULL, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    HGLOBAL hResData = LoadResource (NULL, hResInfo);
    DWORD dwSize = SizeofResource (NULL, hResInfo);
    LPVOID pRes = LockResource (hResData);
    LPVOID pResCopy = LocalAlloc(LMEM_FIXED, dwSize+1000);
    CopyMemory (pResCopy, pRes, dwSize);
    UnlockResource (hResData);
    FreeResource (hResData);
    LocalFree(pResCopy);
}

void setHotkey(){
    RegisterHotKey(NULL,1,0,VK_F1);
    RegisterHotKey(NULL,2,0,VK_F2);
    RegisterHotKey(NULL,3,0,VK_F3);
    RegisterHotKey(NULL,4,0,VK_F4);
    RegisterHotKey(NULL,5,0,VK_F5);
    RegisterHotKey(NULL,6,0,VK_F6);
    RegisterHotKey(NULL,7,0,VK_F7);
    RegisterHotKey(NULL,8,0,VK_F8);
    RegisterHotKey(NULL,9,0,VK_F9);
    // RegisterHotKey(NULL,10,0,VK_XBUTTON2);
    // RegisterHotKey(NULL,11,0,VK_XBUTTON1);
    RegisterHotKey(NULL,12,0,VK_DECIMAL);
    RegisterHotKey(NULL,13,0,VK_NUMPAD0);
    RegisterHotKey(NULL,14,0,VK_NUMPAD1);
    RegisterHotKey(NULL,15,0,VK_NUMPAD2);
    RegisterHotKey(NULL,16,0,VK_NUMPAD3);
    RegisterHotKey(NULL,17,0,VK_ADD);
    RegisterHotKey(NULL,18,0,VK_SUBTRACT);
    RegisterHotKey(NULL,19,0,VK_MULTIPLY);
    RegisterHotKey(NULL,20,0,VK_DIVIDE);
    RegisterHotKey(NULL,21,0,VK_DELETE);

    RegisterHotKey(NULL,22,MOD_SHIFT,VK_F1);
    RegisterHotKey(NULL,23,MOD_SHIFT,VK_F2);
    RegisterHotKey(NULL,24,MOD_SHIFT,VK_F3);
    RegisterHotKey(NULL,25,MOD_SHIFT,VK_F4);
    RegisterHotKey(NULL,26,MOD_SHIFT,VK_F5);
    RegisterHotKey(NULL,27,MOD_SHIFT,VK_F6);
    RegisterHotKey(NULL,28,MOD_SHIFT,VK_F7);
    RegisterHotKey(NULL,29,MOD_SHIFT,VK_F8);
    RegisterHotKey(NULL,30,MOD_SHIFT,VK_F9);
    // RegisterHotKey(NULL,31,MOD_SHIFT,VK_XBUTTON2);
    // RegisterHotKey(NULL,32,MOD_SHIFT,VK_XBUTTON1);
    RegisterHotKey(NULL,33,MOD_SHIFT,VK_DECIMAL);
    RegisterHotKey(NULL,34,MOD_SHIFT,VK_NUMPAD0);
    RegisterHotKey(NULL,35,MOD_SHIFT,VK_NUMPAD1);
    RegisterHotKey(NULL,36,MOD_SHIFT,VK_NUMPAD2);
    RegisterHotKey(NULL,37,MOD_SHIFT,VK_NUMPAD3);
    RegisterHotKey(NULL,38,MOD_SHIFT,VK_ADD);
    RegisterHotKey(NULL,39,MOD_SHIFT,VK_SUBTRACT);
    RegisterHotKey(NULL,40,MOD_SHIFT,VK_MULTIPLY);
    RegisterHotKey(NULL,41,MOD_SHIFT,VK_DIVIDE);
    RegisterHotKey(NULL,42,MOD_SHIFT,VK_DELETE);
}

void keyprint(int key){
    INPUT inputs[2];
    ZeroMemory(inputs, sizeof(inputs)); 
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = key;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = key;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput((sizeof(inputs)/sizeof((inputs)[0])), inputs, sizeof(INPUT));
}

void sendkey(int a, int j){for(int i = 0; i < j; i++)keyprint(a);}

void resetHotkey(){for(int i = 1; i < 43; i++) UnregisterHotKey(NULL,i);}

void keyM(){
    keyprint(0x4d);
    Sleep(50);
}

void noceo(){
    keyM();
    Enter;
    up;
    Enter;
}

void bltDeffult(){
    keyM();
    if(ceo == 0) sendkey(VK_DOWN, 2);
    else sendkey(VK_DOWN, 3);
    Enter;
    sendkey(VK_DOWN, 5);
    Enter;
}

void chet(){
    for(int i = 0; i < 5; i++){
        keyprint(0x54);
        keyprint(VK_SPACE);
        Enter;
    }
}

void swap(){
    if(GetAsyncKeyState(VK_XBUTTON2)){
        keyprint(0x34);
        keyprint(0x32);
    }else if(GetAsyncKeyState(VK_XBUTTON1)){
        keyprint(0x34);
        keyprint(0x33);
    }
}

int offceo(){
    int time = 0;

    MSG msg = { 0 };
    while(ceo == 0){
        if(time == 50){
            processMemory();
            time = 0;
        } 
        GetMessage(&msg, NULL, 0, 0);
        swap();
        if(msg.wParam == 1 || msg.wParam == 22) {
            keyM();
            sendkey(VK_DOWN, 5);
            Enter;
            Enter;
        }else if(msg.wParam == 2 || msg.wParam == 23){
            keyM();
            sendkey(VK_DOWN, 6);
            Enter;
            Enter;
        }else if(msg.wParam == 3 || msg.wParam == 24){
            bltDeffult();
            left;
            down;
            sendkey(VK_LEFT, 2);
            sendkey(VK_DOWN, 2);
            Enter;
            kM;
        }else if(msg.wParam == 4 || msg.wParam == 25){
            bltDeffult();
            sendkey(VK_LEFT, 2);
            down;
            left;
            sendkey(VK_DOWN, 2);
            Enter;
            kM;
        }else if(msg.wParam == 5 || msg.wParam == 26){
            bltDeffult();
            sendkey(VK_LEFT, 4);
            up;
            Enter;
            kM;
        }else if(msg.wParam == 6 || msg.wParam == 27){
            bltDeffult();
            left;
            down;
            sendkey(VK_LEFT, 3);
            sendkey(VK_DOWN, 2);
            Enter;
            kM;
        }else if(msg.wParam == 7 || msg.wParam == 28){
            bltDeffult();
            left;
            up;
            Enter;
            kM;
        }else if(msg.wParam == 8 || msg.wParam == 29){
            bltDeffult();
            left;
            down;
            left;
            sendkey(VK_DOWN, 2);
            Enter;
            kM;
        }else if(msg.wParam == 9 || msg.wParam == 30){
            bltDeffult();
        }else if(msg.wParam == 21 || msg.wParam == 42){
            chet();
        }
        delay;
        time++;
    }
    return 1;
}

int onceo(){
    int time = 0;

    MSG msg = { 0 };
    while(ceo == 1){
        if(time == 50){
            processMemory();
            time = 0;
        } 
        GetMessage(&msg, NULL, 0, 0);

        delay;
        time++;
    }
    return 0;
}

int main(void){
    // HWND hConsole = GetConsoleWindow();
    // ShowWindow(hConsole, SW_HIDE);
    processMemory();
    playUI();
    setHotkey();
    while(1){
        if(ceo == 0) ceo = offceo();
        else if(ceo == 1) ceo = onceo();
        else break;
    }
    resetHotkey();
    return 0;
}

void textcolor(int color_number){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_number);
}

void playUI(){
    textcolor(4);
    SetConsoleTitle("[GTA5 Macro]");
    system("mode con cols=17 lines=10");
    printf(" -Macro Running-\n ---------------\n |-|Developer|-|\n -|--[Sunwoo]-|-\n -|--[Jaeho]--|-\n ---------------\n ---|Sponsor|---\n ---|Sponsor|---\n ---[Yongmin]---\n ---------------");
}
