// Copyright (c) 2020 by the Zeek Project. See LICENSE for details.

#pragma once

#include <ostream>
#include <string>

#include <hilti/rt/type-info.h>

#include "options.h"

/** Render parsed unit into readable text representation. */
class TextPrinter {
public:
    /**
     * Constructor.
     *
     * @param output stream to send output to
     * @param options output controlling specifics of the output
     */
    TextPrinter(std::ostream& output, OutputOptions options) : _output(output), _options(std::move(options)){};

    /**
     * Render one parsed value into text.
     *
     * @param v value representing parsed unit to render
     */
    void print(const hilti::rt::type_info::Value& v);

private:
    // Return output stream.
    std::ostream& out() { return _output; }

    // Insert current indentation into output stream.
    void outputIndent() { out() << std::string(_level * 2, ' '); }

    // Increase indentation level while executing callback function.
    void indent(const std::function<void()>& func) {
        ++_level;
        func();
        --_level;
    }

    std::ostream& _output;  // output stream
    OutputOptions _options; // formatting options
    int _level = 0;         // indentation level
};
