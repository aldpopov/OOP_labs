#pragma once

#include <iostream>
#include <iterator>
#include <memory_resource>
#include <vector>

class MemoryResource : public std::pmr::memory_resource {
    public:
    MemoryResource() = default;
    ~MemoryResource();
    protected:
    void* do_allocate(std::size_t, std::size_t) override;
    void do_deallocate(void*, std::size_t, std::size_t);
    bool do_is_equal(const std::pmr::memory_resource&) const noexcept;
    private:
    std::vector<void*> allocated_blocks;
};