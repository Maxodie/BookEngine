#include <Book.hpp>

struct TestEvent
{
    int32_t data{0};
};

struct MyLayer : Book::AppInterface
{
    BOOK_INLINE void OnStart() override
    {
        BOOK_CORE_INFO("OnStart()");
        AttachCallback<TestEvent>([this] (auto event)
        {
            BOOK_CORE_INFO("Test event : {}", event.data);
            DetachLayer<MyLayer>();
        });
    }

    BOOK_INLINE void OnUpdate() override
    {
        BOOK_CORE_INFO("OnUpdate()");

        if(++m_Counter == 10)
        {
            PostEvent<TestEvent>();
        }
    }

private:
    uint8_t m_Counter {0};
};

int main(int32_t argc, char** argv)
{
    BOOK_CORE_INFO("Editor Started !");

    Book::Application app{};
    app.AttachLayer<MyLayer>();
    app.RunContext();
    return 0;
}
