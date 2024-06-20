#include "book.h"


Book::Book(int id, const std::string& name, const std::string& author)
    : _book_id(id), _book_name(name), _book_author(author) {}

int Book::get_book_id() const {
    return _book_id;
}

std::string Book::get_book_name() const {
    return _book_name;
}

std::string Book::get_author() const {
    return _book_author;
}

BookList::BookList() {
    _book_list = std::vector<Book>();
}

BookList::~BookList() {
    _book_list.clear();
}

void BookList::load_books() {
    std::ifstream file(BOOK_FILE_NAME);
    if (!file) {
        std::cerr << "Error opening file: " << BOOK_FILE_NAME << "\n";
        return;
    }
    if (file.is_open()) {
        int id;
        std::string name, author;
        while (file >> id >> name >> author) {
            _book_list.emplace_back(id, name, author);
            //emplace_back()������C++11�������ԣ�����������ĩβֱ�ӹ������
            //�����push_back(Book(id, name, author))��emplace_back()����һ�ο�������
        }
        file.close();
    }
}

void BookList::save_books() const {
    std::ofstream file(BOOK_FILE_NAME);
    if (!file) {
        std::cerr << "Error opening file: " << BOOK_FILE_NAME << "\n";
        return;
    }
    if (file.is_open()) {
        for (const auto& book : _book_list) {
            file << book.get_book_id() << " "
                << book.get_book_name() << " "
                << book.get_author() << "\n";
        }
        file.close();
    }
}

std::vector<Book> BookList::get_book_list() const {
    return _book_list;
}

void BookList::add_book(const Book& new_book) {
    _book_list.push_back(new_book);
}

void BookList::delete_book(int id) {
    _book_list.erase(
        std::remove_if(_book_list.begin(), _book_list.end(),
            [id](const Book& book) { return book.get_book_id() == id; }),
        _book_list.end());
    //erase(first,last);ɾ����first��last֮����ַ���first��last���ǵ�������
    //remove_if(iterator begin, iterator end, UnaryPredicate p)
    //UnaryPredicate p ��һ��һԪ����������һ������������bool���ͣ��˴���lambda���ʽ,����ص���������Ϊ�棬�򽫵�ǰ��ָ��Ĳ����Ƶ�β��
    //[id](const Book& book) { return book.get_book_id() == id; } ��lambda���ʽ��[id]�ǲ����б�
    //�����б�[id]��ʾ��lambda���ʽ�п���ʹ��id��������������б�������[=]��ʾ�Դ�ֵ��ʽ�������оֲ�������[&]��ʾ�����÷�ʽ�������оֲ�����

    //�ⲿ�ֵĴ������ȼ��book_list.begin()��book_list.end()��book.get_book_id() == id��Ԫ�أ�Ȼ����ЩԪ���Ƶ�β�������eraseɾ��β����Ԫ��
}

void BookList::delete_book(const std::string& name) {
    _book_list.erase(
        std::remove_if(_book_list.begin(), _book_list.end(),
            [&name](const Book& book) { return book.get_book_name() == name; }),
        _book_list.end());
    //ͬ��
}

Book BookList::search_book(int id) const {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [id](const Book& book) { return book.get_book_id() == id; });
    //find_if(iterator begin, iterator end, UnaryPredicate p)
    //UnaryPredicate p ��һ��һԪ����������һ������������bool���ͣ��˴���lambda���ʽ
    //����ص���������Ϊ�棬�򷵻ص�ǰ��ָ��Ĳ���
    if (it != _book_list.end()) {
        return *it;
    }
    else {
        std::cout << "Book not found\n";
        return Book(0, "", "");
    }
}

Book BookList::search_book(const std::string& name) const {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [&name](const Book& book) { return book.get_book_name() == name; });
    //ͬ��
    if (it != _book_list.end()) {
        return *it;
    }
    else {
        std::cout << "Book not found\n";
        return Book(0, "", "");
    }
}

void BookList::revise_book(int id) {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [id](const Book& book) { return book.get_book_id() == id; });
    //ͬ��
    if (it != _book_list.end()) {
        int new_id = _get_input<int>("�������µ����: ");
        std::string new_name = _get_input<std::string>("�������µ�����: ");
        std::string new_author = _get_input<std::string>("�������µ�����: ");
        *it = Book(new_id, new_name, new_author);
    }
    else {
        std::cout << "Book not found\n";
    }
}

void BookList::revise_book(const std::string& name) {
    auto it = std::find_if(_book_list.begin(), _book_list.end(),
        [&name](const Book& book) { return book.get_book_name() == name; });
    //ͬ��
    if (it != _book_list.end()) {
        int new_id = _get_input<int>("�������µ����: ");
        std::string new_name = _get_input<std::string>("�������µ�����: ");
        std::string new_author = _get_input<std::string>("�������µ�����: ");
        *it = Book(new_id, new_name, new_author);
    }
    else {
        std::cout << "Book not found\n";
    }
}

void BookList::show_book_list() const {
    for (const auto& book : _book_list) {
        display_book(book);
    }
}

void BookList::display_book(const Book& book) const {
    std::cout << "�鼮���: " << book.get_book_id() << "\n"
        << "�鼮����: " << book.get_book_name() << "\n"
        << "�鼮����: " << book.get_author() << "\n";
}

template <typename T>
T BookList::_get_input(const std::string& prompt) const {
    std::cout << prompt;
    T value;
    std::cin >> value;
    while (std::cin.fail()) {
        std::cin.clear(); // ��������־
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ����֮ǰ�����������е��ַ�
        std::cout << "Invalid input. Please try again: ";
        std::cin >> value;
    }
    return value;
    //���������һ��ģ�庯�������ڻ�ȡ�û������ֵ��T��ģ��������������������ͣ��������ظ�IO��������
}

std::any BookList::_get_any_input() const{
    std::any value;
    std::string input; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ����֮ǰ�����������еĻ��з�
    std::getline(std::cin, input); // ��ȡ��������

    // ���Խ�����ת��Ϊ����
    try {
        int intValue = std::stoi(input);
        value = intValue; // ����ɹ����洢Ϊint
    }
    catch (const std::invalid_argument& e) {
        // ���ת��ʧ�ܣ��ٶ��������ַ���
        value = input; // �洢Ϊstring

    }
    return value;
}


void BookList::book_management() {
    
    //std::unique_ptr<T>��һ������ָ�룬���ڹ���̬����Ķ��󣬵�unique_ptr�����뿪������ʱ������ָ��Ķ���ᱻ�Զ��ͷ�
    //unique_ptr�����ܱ����ƣ�ֻ�ܱ��ƶ����������Ա����ڴ�й©
    //unique_ptr����������������Զ��ͷ���ָ��Ķ���

    load_books();
    while (true) {
        system("cls");
        std::cout << "1. ����鼮\n";
        std::cout << "2. ɾ���鼮\n";
        std::cout << "3. �����鼮\n";
        std::cout << "4. �޸��鼮\n";
        std::cout << "5. ��ʾ�鼮�б�\n";
        std::cout << "6. �˳�ͼ�����\n";
        std::cout << "��ѡ�������";
        int choice;
        std::cin >> choice;


        switch (choice) {
            //�����c++�е�std::endl��\n���죬��Ϊstd::endl��ˢ�»�����
        case 1: {
            int id = _get_input<int>("�������鼮��ţ�");
            std::string name = _get_input<std::string>("�������鼮���ƣ�");
            std::string author = _get_input<std::string>("���������ߣ�");
            add_book(Book(id, name, author));
            break;
        }
        case 2: {
            std::cout << "������Ҫɾ�����鼮��Ż����鼮����: ";
            std::any value = _get_any_input();
            if (value.has_value()) {
                if (value.type() == typeid(int)) {
                    int id = std::any_cast<int>(value);
                    delete_book(id);
                }
                else if (value.type() == typeid(std::string)) {
                    std::string name = std::any_cast<std::string>(value);
                    delete_book(name);
                }
                //std::any_cast<T>���ڽ�std::any����ת��ΪT���ͣ���ʾת��
                else {
                    std::cerr << "Unsupported type for deleting book" << std::endl;
                }
            }
            else {
                std::cout << "No value provided for deleting book" << std::endl;
            }
            break;
        }
        case 3: {
            Book book(0, "", "");
            std::cout << "������Ҫ���ҵ��鼮��Ż����鼮����: ";
            std::any value = _get_any_input();
            if (value.has_value()) {
                if (value.type() == typeid(int)) {
                    int id = std::any_cast<int>(value);
                    book = search_book(id);
                }
                else if (value.type() == typeid(std::string)) {
                    std::string name = std::any_cast<std::string>(value);
                    book = search_book(name);
                }
                else {
                    std::cerr << "Unsupported type for book" << std::endl;
                }
                display_book(book);
            }
            else {
                std::cout << "No value provided for book" << std::endl;
            }
            break;
        }
        case 4: {
            std::cout << "������Ҫ�޸ĵ��鼮��Ż����鼮����: ";
            std::any value = _get_any_input();
            if (value.has_value()) {
                if (value.type() == typeid(int)) {
                    int id = std::any_cast<int>(value);
                    std::cout << id << std::endl;
                    revise_book(id);
                }
                else if (value.type() == typeid(std::string)) {
                    std::string name = std::any_cast<std::string>(value);
                    revise_book(name);
                }
                else {
                    std::cerr << "Unsupported type for book" << std::endl;
                }
            }
            else {
                std::cout << "No value provided for book" << std::endl;
            }
            break;
        }
        //����ʹ����std::any�����Դ洢�������͵�ֵ��������IO����
        case 5: {
            show_book_list();
            break;
        }
        case 6: {
            save_books();
            return;
            break;
        }
        default: {
            std::cout << "Invalid action\n";
            break;
        }
        }
        //����ʹ��std::map<int, std::function<void()>> commands;����switch-case���
        //�����������Դ���û���Ż����������Ķ�
        system("pause");
    }
}

