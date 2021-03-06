/*
    Copyright (c) 2016, namreeb legal@namreeb.org / http://github.com/namreeb
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
    ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    The views and conclusions contained in the software and documentation are those
    of the authors and should not be interpreted as representing official policies,
    either expressed or implied, of the FreeBSD Project.
*/

#include "Log.hpp"

#include <hadesmem/module.hpp>
#include <hadesmem/find_procedure.hpp>

#include <string>
#include <ostream>

int LogStreamBuffer::sync()
{
    auto newline = str().rfind('\n');

    if (newline != std::wstring::npos)
    {
        std::wstring line = str().substr(0, newline+1);
        str(str().substr(newline));

        m_callBack(line);
    }

    return std::wstringbuf::sync();
}

void WriteLogLine(const std::wstring &line)
{
    std::wofstream out("log.txt", std::ofstream::app);

    out << line;

    out.close();
}

Log::Log(void (*callback)(const std::wstring &)) : m_buffer(callback), std::wostream(&m_buffer) {}

Log gLog(WriteLogLine);

void DebugLogCallback(const std::wstring &line)
{
#ifdef _DEBUG
    MessageBox(nullptr, line.c_str(), L"DEBUG LOG", 0);
#endif
}

Log gDebugLog(DebugLogCallback);
