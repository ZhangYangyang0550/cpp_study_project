#include "lib_management.h"

LibManagement::LibManagement(std::string name = "������ҵ��ѧͼ���") : _name(name){
    _book_list = BookList();
    _reader_list = ReaderList();
}

template <typename T>
T LibManagement::_get_input(const std::string& prompt) const{
    T input;
    std::cout << prompt;
    std::cin >> input;
    return input;
}

void LibManagement::lib_management(){
    while(true){
        system("cls");
        std::cout << "��ӭ����" << _name << "��" << std::endl;
        std::cout << "1. ͼ�����" << std::endl;
        std::cout << "2. ���߹���" << std::endl;
        std::cout << "3. �軹����" << std::endl;
        std::cout << "4. �˳�" << std::endl;
        int choice = _get_input<int>("����������ѡ��");
        switch(choice){
            case 1:
                _book_list.book_management();
                break;
            case 2:
                _reader_list.reader_management();
                break;
            case 3:
                _reader_list.borrow_return_management();
                break;
            case 4:
                return;
            default:
                std::cout << "����������������룡" << std::endl;
        }
    }
    system("pause");

}

int main(){
    LibManagement lib("������ҵ��ѧͼ���");
    lib.lib_management();
    return 0;
}