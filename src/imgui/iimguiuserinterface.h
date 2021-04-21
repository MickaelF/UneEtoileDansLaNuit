#pragma once

class IImGuiUserInterface
{
public:
    IImGuiUserInterface(const char* name);
    ~IImGuiUserInterface();

    virtual void render() = 0;

    bool visible {true};
    const char* name;

private:
};