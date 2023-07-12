#include <eosio/vm/allocator.hpp>

#include <catch2/catch.hpp>

using namespace eosio;
using namespace eosio::vm;

template<typename T>
bool check_alignment(T* ptr) {
   void * p = ptr;
   std::size_t sz = sizeof(T);
   return std::align(alignof(T), sizeof(T), p, sz) != nullptr;
}

TEST_CASE("Testing growable_allocator alignment", "[growable_allocator]") {
   growable_allocator alloc(1024);
   unsigned char * cptr = alloc.alloc<unsigned char>(1);
   CHECK(check_alignment(cptr));
   uint16_t * sptr = alloc.alloc<uint16_t>(1);
   CHECK(check_alignment(sptr));
   uint32_t * iptr = alloc.alloc<uint32_t>(1);
   CHECK(check_alignment(iptr));
   uint64_t * lptr = alloc.alloc<uint64_t>(1);
   CHECK(check_alignment(lptr));
   *cptr = 0x11u;
   *sptr = 0x2233u;
   *iptr = 0x44556677u;
   *lptr = 0x8899102030405060u;
   CHECK(*cptr == 0x11u);
   CHECK(*sptr == 0x2233u);
   CHECK(*iptr == 0x44556677u);
   CHECK(*lptr == 0x8899102030405060u);
}

TEST_CASE("Testing maximum single allocation", "[growable_allocator]") {
   growable_allocator alloc(0);
   char * ptr = alloc.alloc<char>(0x40000000);
   ptr[0] = 'a';
   ptr[0x3FFFFFFF] = 'z';
   alloc.alloc<char>(0);
}


TEST_CASE("Testing maximum multiple allocation", "[growable_allocator]") {
   growable_allocator alloc(1024);
   for(int i = 0; i < 4; ++i) {
      char * ptr = alloc.alloc<char>(0x10000000);
      ptr[0] = 'a';
      ptr[0x0FFFFFFF] = 'z';
   }
   alloc.alloc<char>(0);
}

TEST_CASE("Testing too large single allocation", "[growable_allocator]") {
   growable_allocator alloc(1024);
   CHECK_THROWS_AS(alloc.alloc<char>(0x40000001), wasm_bad_alloc);
}

TEST_CASE("Testing too large multiple allocation", "[growable_allocator]") {
   growable_allocator alloc(1024);
   alloc.alloc<char>(0x10000000);
   alloc.alloc<char>(0x10000000);
   alloc.alloc<char>(0x10000000);
   CHECK_THROWS_AS(alloc.alloc<char>(0x10000001), wasm_bad_alloc);
}

TEST_CASE("Testing maximum initial size", "[growable_allocator]") {
   growable_allocator alloc(0x40000000);
   char * ptr = alloc.alloc<char>(0x40000000);
   ptr[0] = 'a';
   ptr[0x3FFFFFFF] = 'z';
}

TEST_CASE("Testing too large initial size", "[growable_allocator]") {
   CHECK_THROWS_AS(growable_allocator{0x40000001}, wasm_bad_alloc);
   // Check that integer overflow in rounding functions won't cause issues
   CHECK_THROWS_AS(growable_allocator{0x8000000000000000ull}, wasm_bad_alloc);
   CHECK_THROWS_AS(growable_allocator{0xFFFFFFFFFFFE0001ull}, wasm_bad_alloc);
   CHECK_THROWS_AS(growable_allocator{0xFFFFFFFFFFFFFFFFull}, wasm_bad_alloc);
}

TEST_CASE("Testing maximum aligned allocation", "[growable_allocator]") {
   growable_allocator alloc(1024);
   struct alignas(8) aligned_t { char a[8]; };
   alloc.alloc<char>(0x3FFFFFF4);
   aligned_t * ptr = alloc.alloc<aligned_t>(1);
   ptr->a[0] = 'a';
   ptr->a[7] = 'z';
   alloc.alloc<aligned_t>(0);
   CHECK_THROWS_AS(alloc.alloc<char>(1), wasm_bad_alloc);
}

TEST_CASE("Testing reclaim", "[growable_allocator]") {
   growable_allocator alloc(1024);
   int * ptr1 = alloc.alloc<int>(10);
   alloc.reclaim(ptr1 + 2, 8);
   int * ptr2 = alloc.alloc<int>(10);
   CHECK(ptr2 == ptr1 + 2);
}

TEST_CASE("Testing use_default_memory", "[growable_allocator]") {
   growable_allocator alloc(1024);
   // use_default_memory cannot be called when memory is already allocated by constructor
   CHECK_THROWS_AS(alloc.use_default_memory(), wasm_bad_alloc);

   growable_allocator alloc1;
   alloc1.use_default_memory();
   // use_default_memory cannot be called multiple times
   CHECK_THROWS_AS(alloc1.use_default_memory(), wasm_bad_alloc);

   growable_allocator alloc3;
   alloc3.use_default_memory();
   // can allocate as much as researved memory
   alloc3.alloc<char>(growable_allocator::max_memory_size);
   // cannot allocate more than researved memory
   CHECK_THROWS_AS(alloc3.alloc<char>(1), wasm_bad_alloc);
}

TEST_CASE("Testing use_fixed_memory", "[growable_allocator]") {
   growable_allocator alloc(1024);
   // use_fixed_memory cannot be called when memory is already allocated by constructor
   CHECK_THROWS_AS(alloc.use_fixed_memory(false, 4096), wasm_bad_alloc);

   growable_allocator alloc1;
   alloc1.use_fixed_memory(true, 1024);
   // use_fixed_memory cannot be called multiple times
   CHECK_THROWS_AS(alloc1.use_fixed_memory(true, 1024), wasm_bad_alloc);

   growable_allocator alloc2;
   // fixed_memory size cannot be 0
   CHECK_THROWS_AS(alloc2.use_fixed_memory(true, 0), wasm_bad_alloc);
   // fixed_memory size cannot be too big
   CHECK_THROWS_AS(alloc2.use_fixed_memory(true, growable_allocator::max_memory_size + 1), wasm_bad_alloc);
   // fixed_memory size can be growable_allocator::max_memory_size
   alloc2.use_fixed_memory(true, growable_allocator::max_memory_size);

   growable_allocator alloc3;
   // reserved 1024 bytes
   alloc3.use_fixed_memory(true, 1024);
   // can allocate less than researved memory
   alloc3.alloc<char>(1000);
   // can allocate equal to researved memory ( 1000+24 == 1024)
   alloc3.alloc<char>(24);
   // cannot allocate more than researved memory ( 1000+24+1 > 1024)
   CHECK_THROWS_AS(alloc3.alloc<char>(1), wasm_bad_alloc);
}

TEST_CASE("Testing mixed use_fixed_memory and alloc2.use_default_memory", "[growable_allocator]") {
   growable_allocator alloc1;
   alloc1.use_default_memory();
   // use_fixed_memory and use_fixed_memory cannot be mixed
   CHECK_THROWS_AS(alloc1.use_fixed_memory(true, 1024), wasm_bad_alloc);

   growable_allocator alloc2;
   alloc2.use_fixed_memory(true, 1024);
   // use_fixed_memory and use_default_memory cannot be mixed
   CHECK_THROWS_AS(alloc2.use_default_memory(), wasm_bad_alloc);
}
