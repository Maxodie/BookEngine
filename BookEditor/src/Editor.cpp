#include "Window/Event.hpp"
#include <Book.hpp>

struct MyLayer : Book::AppInterface
{
    BOOK_INLINE void OnStart() override
    {
        BOOK_CORE_INFO("OnStart()");
        AttachCallback<Book::MouseMotionEvent>([this] (auto e)
        {
                BOOK_CORE_INFO("Mouse x:{} y:{}", e.TargetX, e.TargetY);
        });
    }

    BOOK_INLINE void OnUpdate() override
    {
    }
};

int main(int32_t argc, char** argv)
{
    BOOK_CORE_INFO("Editor Started !");

    Book::Application app{};
    app.AttachCallback<Book::KeyPressedEvent>([] (auto e)
    {
        BOOK_CORE_INFO("Key: {}", e.Key);
    });


    app.AttachLayer<MyLayer>();
    app.RunContext();
    return 0;
}
