#pragma once

#include <Parsers/IAST.h>
#include <Parsers/ASTLiteral.h>


namespace DB
{


class ASTEnumElement : public IAST
{
public:
    String name;
    Field value;

    ASTEnumElement(const StringRange range, const String & name, const Field & value)
        : IAST{range}, name{name}, value {value} {}

    String getID() const override { return "EnumElement"; }

    ASTPtr clone() const override
    {
        return std::make_shared<ASTEnumElement>(StringRange(), name, value);
    }

protected:
    void formatImpl(const FormatSettings & settings, FormatState & state, FormatStateStacked frame) const override
    {
        frame.need_parens = false;

        const std::string indent_str = settings.one_line ? "" : std::string(4 * frame.indent, ' ');
        settings.ostr << settings.nl_or_ws << indent_str << '\'' << name << "' = " << applyVisitor(FieldVisitorToString{}, value);
    }
};


}
