#include <Book.hpp>

struct Editor : Book::AppInterface
{
    BOOK_INLINE void OnStart() override
    {
        BOOK_CORE_INFO("OnStart()");
    }

    BOOK_INLINE void OnUpdate() override
    {
    }
};

int main(int32_t argc, char** argv)
{
    BOOK_CORE_INFO("Editor Started !");

    Book::Application app{};
    app.AttachLayer<Editor>();
    app.RunContext();
    return 0;
}
