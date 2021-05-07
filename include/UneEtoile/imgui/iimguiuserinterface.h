#pragma once

class IImGuiUserInterface
{
public:
    IImGuiUserInterface(const char* name);
    virtual ~IImGuiUserInterface();

    virtual void render() = 0;

    bool visible {false};
    const char* name;

private:
};