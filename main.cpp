#include <iostream>
#include <sstream>
#include <memory>
#include <string>

class ShareableClass : public std::enable_shared_from_this<ShareableClass>
{
public:

    ShareableClass() {

    }

    virtual ~ShareableClass() = default;

    std::string getValue()
    {
        const void * address = static_cast<const void*>(this);
        std::stringstream ss;
        ss << address;
        std::string name = ss.str();
        return name;
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::weak_ptr<ShareableClass> myWeakPtr;

    //{
        ShareableClass myClass;

        myWeakPtr = myClass.weak_from_this();

        std::cout << "My Class: " << myClass.getValue() << std::endl;
    //}

    //std::shared_ptr<ShareableClass> myClass = std::make_shared<ShareableClass>();

    //std::weak_ptr<ShareableClass> myWeakPtr = myClass->weak_from_this();

    std::shared_ptr<ShareableClass> classPtr = myWeakPtr.lock();
    std::string result("NULL");
    if (classPtr != nullptr)
    {
        result = classPtr->getValue();
    }
    std::cout << "Weak Class: " << result << std::endl;
    std::cout << "Weak Class: " << classPtr->getValue() << std::endl;
    std::cout << "Weak Class: " << myWeakPtr.lock()->getValue() << std::endl;

    return 0;
}