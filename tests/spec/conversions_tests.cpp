#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <catch2/catch.hpp>
#include <utils.hpp>
#include <wasm_config.hpp>
#include <eosio/vm/backend.hpp>

using namespace eosio;
using namespace eosio::vm;
extern wasm_allocator wa;

BACKEND_TEST_CASE( "Testing wasm <conversions_0_wasm>", "[conversions_0_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.0.wasm");
   backend_t bkend( code );
   bkend.set_wasm_allocator( &wa );
   bkend.initialize(nullptr);

   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_s", UINT32_C(0))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_s", UINT32_C(10000))->to_ui64() == UINT32_C(10000));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_s", UINT32_C(4294957296))->to_ui64() == UINT32_C(18446744073709541616));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_s", UINT32_C(4294967295))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_s", UINT32_C(2147483647))->to_ui64() == UINT32_C(2147483647));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_s", UINT32_C(2147483648))->to_ui64() == UINT32_C(18446744071562067968));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_u", UINT32_C(0))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_u", UINT32_C(10000))->to_ui64() == UINT32_C(10000));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_u", UINT32_C(4294957296))->to_ui64() == UINT32_C(4294957296));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_u", UINT32_C(4294967295))->to_ui64() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_u", UINT32_C(2147483647))->to_ui64() == UINT32_C(2147483647));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.extend_i32_u", UINT32_C(2147483648))->to_ui64() == UINT32_C(2147483648));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(18446744073709551615))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(18446744073709451616))->to_ui32() == UINT32_C(4294867296));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(2147483648))->to_ui32() == UINT32_C(2147483648));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(18446744071562067967))->to_ui32() == UINT32_C(2147483647));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(18446744069414584320))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(18446744069414584319))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(18446744069414584321))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(0))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(1311768467463790320))->to_ui32() == UINT32_C(2596069104));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(4294967295))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(4294967296))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.wrap_i64", UINT64_C(4294967297))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(0)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(2147483648)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(1)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(2147483649)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(1065353216)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(1066192077)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(1069547520)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(3212836864)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(3213675725)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(3217031168)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(3220386611)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(3221225472)))->to_ui32() == UINT32_C(4294967294));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(1325400063)))->to_ui32() == UINT32_C(2147483520));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(3472883712)))->to_ui32() == UINT32_C(2147483648));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(1325400064))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(3472883713))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(2139095040))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(4286578688))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(2143289344))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(2141192192))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(4290772992))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_s", bit_cast<float>(UINT32_C(4288675840))), std::exception);
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(0)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(2147483648)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(2147483649)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1065353216)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1066192077)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1069547520)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1072902963)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1073741824)))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1325400064)))->to_ui32() == UINT32_C(2147483648));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1333788671)))->to_ui32() == UINT32_C(4294967040));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(3211159142)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(3212836863)))->to_ui32() == UINT32_C(0));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(1333788672))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(3212836864))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(2139095040))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(4286578688))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(2143289344))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(2141192192))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(4290772992))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f32_u", bit_cast<float>(UINT32_C(4288675840))), std::exception);
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(0)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(9223372036854775808)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(1)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(9223372036854775809)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(4607182418800017408)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(4607632778762754458)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(4609434218613702656)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(13830554455654793216)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(13831004815617530266)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(13832806255468478464)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(13834607695319426662)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(13835058055282163712)))->to_ui32() == UINT32_C(4294967294));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(4746794007244308480)))->to_ui32() == UINT32_C(2147483647));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(13970166044103278592)))->to_ui32() == UINT32_C(2147483648));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(4746794007248502784))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(13970166044105375744))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(9218868437227405312))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(18442240474082181120))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(9221120237041090560))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(9219994337134247936))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(18444492273895866368))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_s", bit_cast<double>(UINT64_C(18443366373989023744))), std::exception);
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(0)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(9223372036854775808)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(1)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(9223372036854775809)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4607182418800017408)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4607632778762754458)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4609434218613702656)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4611235658464650854)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4611686018427387904)))->to_ui32() == UINT32_C(2));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4746794007248502784)))->to_ui32() == UINT32_C(2147483648));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4751297606873776128)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(13829653735729319117)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(13830554455654793215)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4726483295884279808)))->to_ui32() == UINT32_C(100000000));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4751297606875873280))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(13830554455654793216))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4846369599423283200))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(5055640609639927018))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(4890909195324358656))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(9218868437227405312))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(18442240474082181120))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(9221120237041090560))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(9219994337134247936))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(18444492273895866368))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i32.trunc_f64_u", bit_cast<double>(UINT64_C(18443366373989023744))), std::exception);
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(0)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(2147483648)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(1)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(2147483649)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(1065353216)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(1066192077)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(1069547520)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3212836864)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3213675725)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3217031168)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3220386611)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3221225472)))->to_ui64() == UINT32_C(18446744073709551614));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(1333788672)))->to_ui64() == UINT32_C(4294967296));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3481272320)))->to_ui64() == UINT32_C(18446744069414584320));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(1593835519)))->to_ui64() == UINT32_C(9223371487098961920));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3741319168)))->to_ui64() == UINT32_C(9223372036854775808));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(1593835520))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(3741319169))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(2139095040))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(4286578688))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(2143289344))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(2141192192))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(4290772992))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_s", bit_cast<float>(UINT32_C(4288675840))), std::exception);
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(0)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(2147483648)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(1)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(2147483649)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(1065353216)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(1066192077)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(1069547520)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(1333788672)))->to_ui64() == UINT32_C(4294967296));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(1602224127)))->to_ui64() == UINT32_C(18446742974197923840));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(3211159142)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(3212836863)))->to_ui64() == UINT32_C(0));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(1602224128))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(3212836864))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(2139095040))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(4286578688))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(2143289344))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(2141192192))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(4290772992))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f32_u", bit_cast<float>(UINT32_C(4288675840))), std::exception);
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(0)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(9223372036854775808)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(1)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(9223372036854775809)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(4607182418800017408)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(4607632778762754458)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(4609434218613702656)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(13830554455654793216)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(13831004815617530266)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(13832806255468478464)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(13834607695319426662)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(13835058055282163712)))->to_ui64() == UINT32_C(18446744073709551614));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(4751297606875873280)))->to_ui64() == UINT32_C(4294967296));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(13974669643730649088)))->to_ui64() == UINT32_C(18446744069414584320));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(4890909195324358655)))->to_ui64() == UINT32_C(9223372036854774784));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(14114281232179134464)))->to_ui64() == UINT32_C(9223372036854775808));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(4890909195324358656))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(14114281232179134465))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(9218868437227405312))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(18442240474082181120))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(9221120237041090560))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(9219994337134247936))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(18444492273895866368))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_s", bit_cast<double>(UINT64_C(18443366373989023744))), std::exception);
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(0)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(9223372036854775808)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(1)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(9223372036854775809)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4607182418800017408)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4607632778762754458)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4609434218613702656)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4751297606873776128)))->to_ui64() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4751297606875873280)))->to_ui64() == UINT32_C(4294967296));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4895412794951729151)))->to_ui64() == UINT32_C(18446744073709549568));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(13829653735729319117)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(13830554455654793215)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4726483295884279808)))->to_ui64() == UINT32_C(100000000));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4846369599423283200)))->to_ui64() == UINT32_C(10000000000000000));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4890909195324358656)))->to_ui64() == UINT32_C(9223372036854775808));
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(4895412794951729152))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(13830554455654793216))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(9218868437227405312))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(18442240474082181120))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(9221120237041090560))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(9219994337134247936))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(18444492273895866368))), std::exception);
   CHECK_THROWS_AS(bkend(nullptr, "env", "i64.trunc_f64_u", bit_cast<double>(UINT64_C(18443366373989023744))), std::exception);
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(1))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(4294967295))->to_f32()) == UINT32_C(3212836864));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(0))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(2147483647))->to_f32()) == UINT32_C(1325400064));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(2147483648))->to_f32()) == UINT32_C(3472883712));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(1234567890))->to_f32()) == UINT32_C(1318267910));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(16777217))->to_f32()) == UINT32_C(1266679808));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(4278190079))->to_f32()) == UINT32_C(3414163456));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(16777219))->to_f32()) == UINT32_C(1266679810));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_s", UINT32_C(4278190077))->to_f32()) == UINT32_C(3414163458));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(1))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(18446744073709551615))->to_f32()) == UINT32_C(3212836864));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(0))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(9223372036854775807))->to_f32()) == UINT32_C(1593835520));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(9223372036854775808))->to_f32()) == UINT32_C(3741319168));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(314159265358979))->to_f32()) == UINT32_C(1468980468));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(16777217))->to_f32()) == UINT32_C(1266679808));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(18446744073692774399))->to_f32()) == UINT32_C(3414163456));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(16777219))->to_f32()) == UINT32_C(1266679810));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(18446744073692774397))->to_f32()) == UINT32_C(3414163458));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(9223371212221054977))->to_f32()) == UINT32_C(1593835519));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(9223372311732682753))->to_f32()) == UINT32_C(3741319167));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(9007199791611905))->to_f32()) == UINT32_C(1509949441));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_s", UINT64_C(18437736873917939711))->to_f32()) == UINT32_C(3657433089));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_s", UINT32_C(1))->to_f64()) == UINT64_C(4607182418800017408));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_s", UINT32_C(4294967295))->to_f64()) == UINT64_C(13830554455654793216));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_s", UINT32_C(0))->to_f64()) == UINT64_C(0));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_s", UINT32_C(2147483647))->to_f64()) == UINT64_C(4746794007244308480));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_s", UINT32_C(2147483648))->to_f64()) == UINT64_C(13970166044103278592));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_s", UINT32_C(987654321))->to_f64()) == UINT64_C(4741568253304766464));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(1))->to_f64()) == UINT64_C(4607182418800017408));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(18446744073709551615))->to_f64()) == UINT64_C(13830554455654793216));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(0))->to_f64()) == UINT64_C(0));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(9223372036854775807))->to_f64()) == UINT64_C(4890909195324358656));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(9223372036854775808))->to_f64()) == UINT64_C(14114281232179134464));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(4669201609102990))->to_f64()) == UINT64_C(4841535201405015694));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(9007199254740993))->to_f64()) == UINT64_C(4845873199050653696));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(18437736874454810623))->to_f64()) == UINT64_C(14069245235905429504));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(9007199254740995))->to_f64()) == UINT64_C(4845873199050653698));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_s", UINT64_C(18437736874454810621))->to_f64()) == UINT64_C(14069245235905429506));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(1))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(0))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(2147483647))->to_f32()) == UINT32_C(1325400064));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(2147483648))->to_f32()) == UINT32_C(1325400064));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(305419896))->to_f32()) == UINT32_C(1301390004));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(4294967295))->to_f32()) == UINT32_C(1333788672));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(2147483776))->to_f32()) == UINT32_C(1325400064));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(2147483777))->to_f32()) == UINT32_C(1325400065));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(2147483778))->to_f32()) == UINT32_C(1325400065));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(4294966912))->to_f32()) == UINT32_C(1333788670));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(4294966913))->to_f32()) == UINT32_C(1333788671));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(4294966914))->to_f32()) == UINT32_C(1333788671));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(16777217))->to_f32()) == UINT32_C(1266679808));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i32_u", UINT32_C(16777219))->to_f32()) == UINT32_C(1266679810));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(1))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(0))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(9223372036854775807))->to_f32()) == UINT32_C(1593835520));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(9223372036854775808))->to_f32()) == UINT32_C(1593835520));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(18446744073709551615))->to_f32()) == UINT32_C(1602224128));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(16777217))->to_f32()) == UINT32_C(1266679808));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(16777219))->to_f32()) == UINT32_C(1266679810));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(9007199791611905))->to_f32()) == UINT32_C(1509949441));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(9223371761976868863))->to_f32()) == UINT32_C(1593835519));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(9223372586610589697))->to_f32()) == UINT32_C(1593835521));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.convert_i64_u", UINT64_C(18446742424442109953))->to_f32()) == UINT32_C(1602224127));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_u", UINT32_C(1))->to_f64()) == UINT64_C(4607182418800017408));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_u", UINT32_C(0))->to_f64()) == UINT64_C(0));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_u", UINT32_C(2147483647))->to_f64()) == UINT64_C(4746794007244308480));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_u", UINT32_C(2147483648))->to_f64()) == UINT64_C(4746794007248502784));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i32_u", UINT32_C(4294967295))->to_f64()) == UINT64_C(4751297606873776128));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(1))->to_f64()) == UINT64_C(4607182418800017408));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(0))->to_f64()) == UINT64_C(0));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(9223372036854775807))->to_f64()) == UINT64_C(4890909195324358656));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(9223372036854775808))->to_f64()) == UINT64_C(4890909195324358656));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(18446744073709551615))->to_f64()) == UINT64_C(4895412794951729152));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(9223372036854776832))->to_f64()) == UINT64_C(4890909195324358656));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(9223372036854776833))->to_f64()) == UINT64_C(4890909195324358657));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(9223372036854776834))->to_f64()) == UINT64_C(4890909195324358657));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(18446744073709548544))->to_f64()) == UINT64_C(4895412794951729150));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(18446744073709548545))->to_f64()) == UINT64_C(4895412794951729151));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(18446744073709548546))->to_f64()) == UINT64_C(4895412794951729151));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(9007199254740993))->to_f64()) == UINT64_C(4845873199050653696));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.convert_i64_u", UINT64_C(9007199254740995))->to_f64()) == UINT64_C(4845873199050653698));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(0)))->to_f64()) == UINT64_C(0));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(2147483648)))->to_f64()) == UINT64_C(9223372036854775808));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(1)))->to_f64()) == UINT64_C(3936146074321813504));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(2147483649)))->to_f64()) == UINT64_C(13159518111176589312));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(1065353216)))->to_f64()) == UINT64_C(4607182418800017408));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(3212836864)))->to_f64()) == UINT64_C(13830554455654793216));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(4286578687)))->to_f64()) == UINT64_C(14407015207421345792));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(2139095039)))->to_f64()) == UINT64_C(5183643170566569984));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(67108864)))->to_f64()) == UINT64_C(4071254063142928384));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(2118632255)))->to_f64()) == UINT64_C(5172657297058430976));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(2139095040)))->to_f64()) == UINT64_C(9218868437227405312));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(4286578688)))->to_f64()) == UINT64_C(18442240474082181120));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(2143289344)))));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(2141192192)))));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(4290772992)))));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f64.promote_f32", bit_cast<float>(UINT32_C(4288675840)))));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(0)))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(9223372036854775808)))->to_f32()) == UINT32_C(2147483648));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(1)))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(9223372036854775809)))->to_f32()) == UINT32_C(2147483648));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182418800017408)))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(13830554455654793216)))->to_f32()) == UINT32_C(3212836864));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4039728865214464000)))->to_f32()) == UINT32_C(8388608));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(13263100902069239808)))->to_f32()) == UINT32_C(2155872256));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4039728865214463999)))->to_f32()) == UINT32_C(8388607));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(13263100902069239807)))->to_f32()) == UINT32_C(2155872255));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(3936146074321813504)))->to_f32()) == UINT32_C(1));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(13159518111176589312)))->to_f32()) == UINT32_C(2147483649));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(5183643170298134528)))->to_f32()) == UINT32_C(2139095038));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(14407015207152910336)))->to_f32()) == UINT32_C(4286578686));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(5183643170298134529)))->to_f32()) == UINT32_C(2139095039));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(14407015207152910337)))->to_f32()) == UINT32_C(4286578687));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(5183643170566569984)))->to_f32()) == UINT32_C(2139095039));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(14407015207421345792)))->to_f32()) == UINT32_C(4286578687));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(5183643170835005439)))->to_f32()) == UINT32_C(2139095039));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(14407015207689781247)))->to_f32()) == UINT32_C(4286578687));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(5183643170835005440)))->to_f32()) == UINT32_C(2139095040));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(14407015207689781248)))->to_f32()) == UINT32_C(4286578688));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4071254063142928384)))->to_f32()) == UINT32_C(67108864));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(5172657297058430976)))->to_f32()) == UINT32_C(2118632255));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(9218868437227405312)))->to_f32()) == UINT32_C(2139095040));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(18442240474082181120)))->to_f32()) == UINT32_C(4286578688));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182418800017409)))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182418800017407)))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182419068452864)))->to_f32()) == UINT32_C(1065353216));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182419068452865)))->to_f32()) == UINT32_C(1065353217));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182419605323775)))->to_f32()) == UINT32_C(1065353217));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182419605323776)))->to_f32()) == UINT32_C(1065353218));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4607182420142194688)))->to_f32()) == UINT32_C(1065353218));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4715268810125344768)))->to_f32()) == UINT32_C(1266679808));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4715268810125344769)))->to_f32()) == UINT32_C(1266679809));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4715268810662215679)))->to_f32()) == UINT32_C(1266679809));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4715268810662215680)))->to_f32()) == UINT32_C(1266679810));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(5094955347580439664)))->to_f32()) == UINT32_C(1973901096));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4101111194527827589)))->to_f32()) == UINT32_C(122722105));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4038806939559600639)))->to_f32()) == UINT32_C(7529997));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(13836913116900734306)))->to_f32()) == UINT32_C(3224680794));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(14338315240173327556)))->to_f32()) == UINT32_C(4158615026));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(9221120237041090560)))));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(9219994337134247936)))));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(18444492273895866368)))));
   CHECK(check_nan(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(18443366373989023744)))));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(4503599627370496)))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(9227875636482146304)))->to_f32()) == UINT32_C(2147483648));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(3931642474694443008)))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(13155014511549218816)))->to_f32()) == UINT32_C(2147483648));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(3931642474694443009)))->to_f32()) == UINT32_C(1));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.demote_f64", bit_cast<double>(UINT64_C(13155014511549218817)))->to_f32()) == UINT32_C(2147483649));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(0))->to_f32()) == UINT32_C(0));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(2147483648))->to_f32()) == UINT32_C(2147483648));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(1))->to_f32()) == UINT32_C(1));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(4294967295))->to_f32()) == UINT32_C(4294967295));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(123456789))->to_f32()) == UINT32_C(123456789));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(2147483649))->to_f32()) == UINT32_C(2147483649));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(2139095040))->to_f32()) == UINT32_C(2139095040));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(4286578688))->to_f32()) == UINT32_C(4286578688));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(2143289344))->to_f32()) == UINT32_C(2143289344));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(4290772992))->to_f32()) == UINT32_C(4290772992));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(2141192192))->to_f32()) == UINT32_C(2141192192));
   CHECK(bit_cast<uint32_t>(bkend.call_with_return(nullptr, "env", "f32.reinterpret_i32", UINT32_C(4288675840))->to_f32()) == UINT32_C(4288675840));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(0))->to_f64()) == UINT64_C(0));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(1))->to_f64()) == UINT64_C(1));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(18446744073709551615))->to_f64()) == UINT64_C(18446744073709551615));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(9223372036854775808))->to_f64()) == UINT64_C(9223372036854775808));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(1234567890))->to_f64()) == UINT64_C(1234567890));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(9223372036854775809))->to_f64()) == UINT64_C(9223372036854775809));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(9218868437227405312))->to_f64()) == UINT64_C(9218868437227405312));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(18442240474082181120))->to_f64()) == UINT64_C(18442240474082181120));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(9221120237041090560))->to_f64()) == UINT64_C(9221120237041090560));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(18444492273895866368))->to_f64()) == UINT64_C(18444492273895866368));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(9219994337134247936))->to_f64()) == UINT64_C(9219994337134247936));
   CHECK(bit_cast<uint64_t>(bkend.call_with_return(nullptr, "env", "f64.reinterpret_i64", UINT64_C(18443366373989023744))->to_f64()) == UINT64_C(18443366373989023744));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(0)))->to_ui32() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(2147483648)))->to_ui32() == UINT32_C(2147483648));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(1)))->to_ui32() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(4294967295)))->to_ui32() == UINT32_C(4294967295));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(2147483649)))->to_ui32() == UINT32_C(2147483649));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(1065353216)))->to_ui32() == UINT32_C(1065353216));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(1078530010)))->to_ui32() == UINT32_C(1078530010));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(2139095039)))->to_ui32() == UINT32_C(2139095039));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(4286578687)))->to_ui32() == UINT32_C(4286578687));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(2139095040)))->to_ui32() == UINT32_C(2139095040));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(4286578688)))->to_ui32() == UINT32_C(4286578688));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(2143289344)))->to_ui32() == UINT32_C(2143289344));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(4290772992)))->to_ui32() == UINT32_C(4290772992));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(2141192192)))->to_ui32() == UINT32_C(2141192192));
   CHECK(bkend.call_with_return(nullptr, "env", "i32.reinterpret_f32", bit_cast<float>(UINT32_C(4288675840)))->to_ui32() == UINT32_C(4288675840));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(0)))->to_ui64() == UINT32_C(0));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(9223372036854775808)))->to_ui64() == UINT32_C(9223372036854775808));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(1)))->to_ui64() == UINT32_C(1));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(18446744073709551615)))->to_ui64() == UINT32_C(18446744073709551615));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(9223372036854775809)))->to_ui64() == UINT32_C(9223372036854775809));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(4607182418800017408)))->to_ui64() == UINT32_C(4607182418800017408));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(4614256656552045841)))->to_ui64() == UINT32_C(4614256656552045841));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(9218868437227405311)))->to_ui64() == UINT32_C(9218868437227405311));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(18442240474082181119)))->to_ui64() == UINT32_C(18442240474082181119));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(9218868437227405312)))->to_ui64() == UINT32_C(9218868437227405312));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(18442240474082181120)))->to_ui64() == UINT32_C(18442240474082181120));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(9221120237041090560)))->to_ui64() == UINT32_C(9221120237041090560));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(18444492273895866368)))->to_ui64() == UINT32_C(18444492273895866368));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(9219994337134247936)))->to_ui64() == UINT32_C(9219994337134247936));
   CHECK(bkend.call_with_return(nullptr, "env", "i64.reinterpret_f64", bit_cast<double>(UINT64_C(18443366373989023744)))->to_ui64() == UINT32_C(18443366373989023744));
}

BACKEND_TEST_CASE( "Testing wasm <conversions_1_wasm>", "[conversions_1_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.1.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_10_wasm>", "[conversions_10_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.10.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_11_wasm>", "[conversions_11_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.11.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_12_wasm>", "[conversions_12_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.12.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_13_wasm>", "[conversions_13_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.13.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_14_wasm>", "[conversions_14_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.14.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_15_wasm>", "[conversions_15_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.15.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_16_wasm>", "[conversions_16_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.16.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_17_wasm>", "[conversions_17_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.17.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_18_wasm>", "[conversions_18_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.18.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_19_wasm>", "[conversions_19_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.19.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_2_wasm>", "[conversions_2_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.2.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_20_wasm>", "[conversions_20_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.20.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_21_wasm>", "[conversions_21_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.21.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_22_wasm>", "[conversions_22_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.22.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_23_wasm>", "[conversions_23_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.23.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_24_wasm>", "[conversions_24_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.24.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_25_wasm>", "[conversions_25_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.25.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_3_wasm>", "[conversions_3_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.3.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_4_wasm>", "[conversions_4_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.4.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_5_wasm>", "[conversions_5_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.5.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_6_wasm>", "[conversions_6_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.6.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_7_wasm>", "[conversions_7_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.7.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_8_wasm>", "[conversions_8_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.8.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

BACKEND_TEST_CASE( "Testing wasm <conversions_9_wasm>", "[conversions_9_wasm_tests]" ) {
   using backend_t = backend<std::nullptr_t, TestType>;
   auto code = backend_t::read_wasm( std::string(wasm_directory) + "conversions.9.wasm");
   CHECK_THROWS_AS(backend_t(code), std::exception);
}

