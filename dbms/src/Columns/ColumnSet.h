#pragma once

#include <Columns/IColumnDummy.h>


namespace DB
{

class Set;
using ConstSetPtr = std::shared_ptr<const Set>;


/** A column containing multiple values in the `IN` section.
  * Behaves like a constant-column (because the set is one, not its own for each line).
  * This column has a nonstandard value, so it can not be obtained via a normal interface.
  */
class ColumnSet final : public IColumnDummy
{
public:
    ColumnSet(size_t s_, const ConstSetPtr & data_) : IColumnDummy(s_), data(data_) {}

    const char * getFamilyName() const override { return "Set"; }
    ColumnPtr cloneDummy(size_t s_) const override { return std::make_shared<ColumnSet>(s_, data); }

    ConstSetPtr getData() const { return data; }

private:
    ConstSetPtr data;
};

}
