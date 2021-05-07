#pragma once

class AbstractShader
{
public:
    AbstractShader(const char* name);
    virtual ~AbstractShader();

    const char* name;
    virtual int id() const = 0;

    virtual void activate() const = 0;
};