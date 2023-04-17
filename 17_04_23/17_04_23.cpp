//потоки 
#include <iostream>
#include<Windows.h>
#include<stdio.h>//fopen_s(const char *filename, const char* mode(режим открытия) )//
//fclose(FILE* file); EOF - возвращает в случае ошибки 
//fgets() // принимает указатель на строку, количество элементов под строку, *файл 
//fputs(const char* string, File* file) // построчная запись файла


//fread(void buffer, size_t size - размер элемента в байтах, size_t count- максимальное кол во элементов в файле, FILE* file);
//fwrite(const void* buffer, size_t size, size_t count, FOLE* file);//возращает число равное количеству байтов записанных

//int _fileno(FILE* file) - возвращает дикриптор файла(дискриптор -уникальный номер)
// fseek( FILE* file, int offset)-смещение по файлу int whencel -точка начала перемещениея 1, SEEK_SET(0), SEEK_CUR(1), SEEK_END(2)
//

#include<io.h>
//int _access(const char* path, int mode- на какие разрещения проверить файл,)-определяет разрещения файла, директори 
//00 проверка на существование файла
//02 проверка на разрешена ли запись файла
//04 - разрешено ли чтение файла 
// 06 - проверка разрешено чтение и запись для файла 
// long _filelenngth(int handle- дискриптор файла )- возвращает размер файла в байтах, если ошибка возвращает-1;
//int _locking (int handle, int mode-типы блокировки , long nbytes)- разблокирует байты файла, начиная с текущей позиции
// _LK_LOCK- блокирует байты, потворная попытк ане чаже 1 сек и только 10 , если не вышло то -1
// _LK_ТИLCK-единожды пробует заблокировать
// _LK_UNLCK - разблокирует байты
//
using namespace std;
void Russ( const char* str) {
    char mass[100];
    CharToOemA(str, mass);
    cout << mass;
}
bool CopyFiles(char* sou, char* des) {
    const int size = 65536;
    FILE* src, * dest;
    if (fopen_s(&src, sou, "rb")) return false;
    size_t handle = _fileno(src);

    char* data = new char[size];
    if (fopen_s(&dest, des, "wd")) return false;
    size_t rea;
    while (!feof(src)) {
        rea = fread(data, sizeof(char), size, src);
        fwrite(data, sizeof(char), rea, dest);

    }
    fclose(src);
    fclose(dest);
    return true;


}

void main()
{
    char sourse[_MAX_PATH];//максимальный размер пути
    char destin[_MAX_PATH];//куда нужно скопировать
    char answer[20];
    Russ(" Вbедите путь и название  копируемого файла");
    cin.getline(sourse, _MAX_PATH);

    if (_access(sourse, 00) == 0) {// проверка существования файла 
        Russ(" Этот файл не существует");
        return;

        Russ(" Вbедите путь и название  копируемого файла");
        cin.getline(destin, _MAX_PATH);
        if (_access(sourse, 00) == -1) {
            Russ(" Этот файл уже сущетсвут Перезаписать? (1-да /2-нет)");
            cin.getline(answer, 20);//нужно ли перезаписать, указали размер 
            if (!strcmp(answer, "2")) {
                Russ(" \n Отмена операции");
                return;
            }
            else if (strcmp(answer, "1")) {
                Russ(" \n неправленый ввод ");
                return;
            }
            if (_access(destin, 02)) {
                Russ(" \n не доступа для записи  ");
            }
            if (!CopyFiles(sourse, destin)) {
                Russ(" \n Ошибка при работе с фалами   ");
            }
        }
    }

}

