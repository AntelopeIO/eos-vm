set(SOFTFLOAT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/softfloat)
set(SOFTFLOAT_SRC ${SOFTFLOAT_ROOT}/source)
set(SOFTFLOAT_BUILD ${SOFTFLOAT_ROOT}/build)

set(softfloat_sources
    ${SOFTFLOAT_SRC}/s_eq128.c
    ${SOFTFLOAT_SRC}/s_le128.c
    ${SOFTFLOAT_SRC}/s_lt128.c
    ${SOFTFLOAT_SRC}/s_shortShiftLeft128.c
    ${SOFTFLOAT_SRC}/s_shortShiftRight128.c
    ${SOFTFLOAT_SRC}/s_shortShiftRightJam64.c
    ${SOFTFLOAT_SRC}/s_shortShiftRightJam64Extra.c
    ${SOFTFLOAT_SRC}/s_shortShiftRightJam128.c
    ${SOFTFLOAT_SRC}/s_shortShiftRightJam128Extra.c
    ${SOFTFLOAT_SRC}/s_shiftRightJam32.c
    ${SOFTFLOAT_SRC}/s_shiftRightJam64.c
    ${SOFTFLOAT_SRC}/s_shiftRightJam64Extra.c
    ${SOFTFLOAT_SRC}/s_shiftRightJam128.c
    ${SOFTFLOAT_SRC}/s_shiftRightJam128Extra.c
    ${SOFTFLOAT_SRC}/s_shiftRightJam256M.c
    ${SOFTFLOAT_SRC}/s_countLeadingZeros8.c
    ${SOFTFLOAT_SRC}/s_countLeadingZeros16.c
    ${SOFTFLOAT_SRC}/s_countLeadingZeros32.c
    ${SOFTFLOAT_SRC}/s_countLeadingZeros64.c
    ${SOFTFLOAT_SRC}/s_add128.c
    ${SOFTFLOAT_SRC}/s_add256M.c
    ${SOFTFLOAT_SRC}/s_sub128.c
    ${SOFTFLOAT_SRC}/s_sub256M.c
    ${SOFTFLOAT_SRC}/s_mul64ByShifted32To128.c
    ${SOFTFLOAT_SRC}/s_mul64To128.c
    ${SOFTFLOAT_SRC}/s_mul128By32.c
    ${SOFTFLOAT_SRC}/s_mul128To256M.c
    ${SOFTFLOAT_SRC}/s_approxRecip_1Ks.c
    ${SOFTFLOAT_SRC}/s_approxRecip32_1.c
    ${SOFTFLOAT_SRC}/s_approxRecipSqrt_1Ks.c
    ${SOFTFLOAT_SRC}/s_approxRecipSqrt32_1.c
    ${SOFTFLOAT_SRC}/8086-SSE/softfloat_raiseFlags.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_f16UIToCommonNaN.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_commonNaNToF16UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_propagateNaNF16UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_f32UIToCommonNaN.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_commonNaNToF32UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_propagateNaNF32UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_f64UIToCommonNaN.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_commonNaNToF64UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_propagateNaNF64UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/extF80M_isSignalingNaN.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_extF80UIToCommonNaN.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_commonNaNToExtF80UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_propagateNaNExtF80UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/f128M_isSignalingNaN.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_f128UIToCommonNaN.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_commonNaNToF128UI.c
    ${SOFTFLOAT_SRC}/8086-SSE/s_propagateNaNF128UI.c
    ${SOFTFLOAT_SRC}/s_roundToUI32.c
    ${SOFTFLOAT_SRC}/s_roundToUI64.c
    ${SOFTFLOAT_SRC}/s_roundToI32.c
    ${SOFTFLOAT_SRC}/s_roundToI64.c
    ${SOFTFLOAT_SRC}/s_normSubnormalF16Sig.c
    ${SOFTFLOAT_SRC}/s_roundPackToF16.c
    ${SOFTFLOAT_SRC}/s_normRoundPackToF16.c
    ${SOFTFLOAT_SRC}/s_addMagsF16.c
    ${SOFTFLOAT_SRC}/s_subMagsF16.c
    ${SOFTFLOAT_SRC}/s_mulAddF16.c
    ${SOFTFLOAT_SRC}/s_normSubnormalF32Sig.c
    ${SOFTFLOAT_SRC}/s_roundPackToF32.c
    ${SOFTFLOAT_SRC}/s_normRoundPackToF32.c
    ${SOFTFLOAT_SRC}/s_addMagsF32.c
    ${SOFTFLOAT_SRC}/s_subMagsF32.c
    ${SOFTFLOAT_SRC}/s_mulAddF32.c
    ${SOFTFLOAT_SRC}/s_normSubnormalF64Sig.c
    ${SOFTFLOAT_SRC}/s_roundPackToF64.c
    ${SOFTFLOAT_SRC}/s_normRoundPackToF64.c
    ${SOFTFLOAT_SRC}/s_addMagsF64.c
    ${SOFTFLOAT_SRC}/s_subMagsF64.c
    ${SOFTFLOAT_SRC}/s_mulAddF64.c
    ${SOFTFLOAT_SRC}/s_normSubnormalExtF80Sig.c
    ${SOFTFLOAT_SRC}/s_roundPackToExtF80.c
    ${SOFTFLOAT_SRC}/s_normRoundPackToExtF80.c
    ${SOFTFLOAT_SRC}/s_addMagsExtF80.c
    ${SOFTFLOAT_SRC}/s_subMagsExtF80.c
    ${SOFTFLOAT_SRC}/s_normSubnormalF128Sig.c
    ${SOFTFLOAT_SRC}/s_roundPackToF128.c
    ${SOFTFLOAT_SRC}/s_normRoundPackToF128.c
    ${SOFTFLOAT_SRC}/s_addMagsF128.c
    ${SOFTFLOAT_SRC}/s_subMagsF128.c
    ${SOFTFLOAT_SRC}/s_mulAddF128.c
    ${SOFTFLOAT_SRC}/softfloat_state.c
    ${SOFTFLOAT_SRC}/ui32_to_f16.c
    ${SOFTFLOAT_SRC}/ui32_to_f32.c
    ${SOFTFLOAT_SRC}/ui32_to_f64.c
    ${SOFTFLOAT_SRC}/ui32_to_extF80.c
    ${SOFTFLOAT_SRC}/ui32_to_extF80M.c
    ${SOFTFLOAT_SRC}/ui32_to_f128.c
    ${SOFTFLOAT_SRC}/ui32_to_f128M.c
    ${SOFTFLOAT_SRC}/ui64_to_f16.c
    ${SOFTFLOAT_SRC}/ui64_to_f32.c
    ${SOFTFLOAT_SRC}/ui64_to_f64.c
    ${SOFTFLOAT_SRC}/ui64_to_extF80.c
    ${SOFTFLOAT_SRC}/ui64_to_extF80M.c
    ${SOFTFLOAT_SRC}/ui64_to_f128.c
    ${SOFTFLOAT_SRC}/ui64_to_f128M.c
    ${SOFTFLOAT_SRC}/i32_to_f16.c
    ${SOFTFLOAT_SRC}/i32_to_f32.c
    ${SOFTFLOAT_SRC}/i32_to_f64.c
    ${SOFTFLOAT_SRC}/i32_to_extF80.c
    ${SOFTFLOAT_SRC}/i32_to_extF80M.c
    ${SOFTFLOAT_SRC}/i32_to_f128.c
    ${SOFTFLOAT_SRC}/i32_to_f128M.c
    ${SOFTFLOAT_SRC}/i64_to_f16.c
    ${SOFTFLOAT_SRC}/i64_to_f32.c
    ${SOFTFLOAT_SRC}/i64_to_f64.c
    ${SOFTFLOAT_SRC}/i64_to_extF80.c
    ${SOFTFLOAT_SRC}/i64_to_extF80M.c
    ${SOFTFLOAT_SRC}/i64_to_f128.c
    ${SOFTFLOAT_SRC}/i64_to_f128M.c
    ${SOFTFLOAT_SRC}/f16_to_ui32.c
    ${SOFTFLOAT_SRC}/f16_to_ui64.c
    ${SOFTFLOAT_SRC}/f16_to_i32.c
    ${SOFTFLOAT_SRC}/f16_to_i64.c
    ${SOFTFLOAT_SRC}/f16_to_ui32_r_minMag.c
    ${SOFTFLOAT_SRC}/f16_to_ui64_r_minMag.c
    ${SOFTFLOAT_SRC}/f16_to_i32_r_minMag.c
    ${SOFTFLOAT_SRC}/f16_to_i64_r_minMag.c
    ${SOFTFLOAT_SRC}/f16_to_f32.c
    ${SOFTFLOAT_SRC}/f16_to_f64.c
    ${SOFTFLOAT_SRC}/f16_to_extF80.c
    ${SOFTFLOAT_SRC}/f16_to_extF80M.c
    ${SOFTFLOAT_SRC}/f16_to_f128.c
    ${SOFTFLOAT_SRC}/f16_to_f128M.c
    ${SOFTFLOAT_SRC}/f16_roundToInt.c
    ${SOFTFLOAT_SRC}/f16_add.c
    ${SOFTFLOAT_SRC}/f16_sub.c
    ${SOFTFLOAT_SRC}/f16_mul.c
    ${SOFTFLOAT_SRC}/f16_mulAdd.c
    ${SOFTFLOAT_SRC}/f16_div.c
    ${SOFTFLOAT_SRC}/f16_rem.c
    ${SOFTFLOAT_SRC}/f16_sqrt.c
    ${SOFTFLOAT_SRC}/f16_eq.c
    ${SOFTFLOAT_SRC}/f16_le.c
    ${SOFTFLOAT_SRC}/f16_lt.c
    ${SOFTFLOAT_SRC}/f16_eq_signaling.c
    ${SOFTFLOAT_SRC}/f16_le_quiet.c
    ${SOFTFLOAT_SRC}/f16_lt_quiet.c
    ${SOFTFLOAT_SRC}/f16_isSignalingNaN.c
    ${SOFTFLOAT_SRC}/f32_to_ui32.c
    ${SOFTFLOAT_SRC}/f32_to_ui64.c
    ${SOFTFLOAT_SRC}/f32_to_i32.c
    ${SOFTFLOAT_SRC}/f32_to_i64.c
    ${SOFTFLOAT_SRC}/f32_to_ui32_r_minMag.c
    ${SOFTFLOAT_SRC}/f32_to_ui64_r_minMag.c
    ${SOFTFLOAT_SRC}/f32_to_i32_r_minMag.c
    ${SOFTFLOAT_SRC}/f32_to_i64_r_minMag.c
    ${SOFTFLOAT_SRC}/f32_to_f16.c
    ${SOFTFLOAT_SRC}/f32_to_f64.c
    ${SOFTFLOAT_SRC}/f32_to_extF80.c
    ${SOFTFLOAT_SRC}/f32_to_extF80M.c
    ${SOFTFLOAT_SRC}/f32_to_f128.c
    ${SOFTFLOAT_SRC}/f32_to_f128M.c
    ${SOFTFLOAT_SRC}/f32_roundToInt.c
    ${SOFTFLOAT_SRC}/f32_add.c
    ${SOFTFLOAT_SRC}/f32_sub.c
    ${SOFTFLOAT_SRC}/f32_mul.c
    ${SOFTFLOAT_SRC}/f32_mulAdd.c
    ${SOFTFLOAT_SRC}/f32_div.c
    ${SOFTFLOAT_SRC}/f32_rem.c
    ${SOFTFLOAT_SRC}/f32_sqrt.c
    ${SOFTFLOAT_SRC}/f32_eq.c
    ${SOFTFLOAT_SRC}/f32_le.c
    ${SOFTFLOAT_SRC}/f32_lt.c
    ${SOFTFLOAT_SRC}/f32_eq_signaling.c
    ${SOFTFLOAT_SRC}/f32_le_quiet.c
    ${SOFTFLOAT_SRC}/f32_lt_quiet.c
    ${SOFTFLOAT_SRC}/f32_isSignalingNaN.c
    ${SOFTFLOAT_SRC}/f64_to_ui32.c
    ${SOFTFLOAT_SRC}/f64_to_ui64.c
    ${SOFTFLOAT_SRC}/f64_to_i32.c
    ${SOFTFLOAT_SRC}/f64_to_i64.c
    ${SOFTFLOAT_SRC}/f64_to_ui32_r_minMag.c
    ${SOFTFLOAT_SRC}/f64_to_ui64_r_minMag.c
    ${SOFTFLOAT_SRC}/f64_to_i32_r_minMag.c
    ${SOFTFLOAT_SRC}/f64_to_i64_r_minMag.c
    ${SOFTFLOAT_SRC}/f64_to_f16.c
    ${SOFTFLOAT_SRC}/f64_to_f32.c
    ${SOFTFLOAT_SRC}/f64_to_extF80.c
    ${SOFTFLOAT_SRC}/f64_to_extF80M.c
    ${SOFTFLOAT_SRC}/f64_to_f128.c
    ${SOFTFLOAT_SRC}/f64_to_f128M.c
    ${SOFTFLOAT_SRC}/f64_roundToInt.c
    ${SOFTFLOAT_SRC}/f64_add.c
    ${SOFTFLOAT_SRC}/f64_sub.c
    ${SOFTFLOAT_SRC}/f64_mul.c
    ${SOFTFLOAT_SRC}/f64_mulAdd.c
    ${SOFTFLOAT_SRC}/f64_div.c
    ${SOFTFLOAT_SRC}/f64_rem.c
    ${SOFTFLOAT_SRC}/f64_sqrt.c
    ${SOFTFLOAT_SRC}/f64_eq.c
    ${SOFTFLOAT_SRC}/f64_le.c
    ${SOFTFLOAT_SRC}/f64_lt.c
    ${SOFTFLOAT_SRC}/f64_eq_signaling.c
    ${SOFTFLOAT_SRC}/f64_le_quiet.c
    ${SOFTFLOAT_SRC}/f64_lt_quiet.c
    ${SOFTFLOAT_SRC}/f64_isSignalingNaN.c
    ${SOFTFLOAT_SRC}/extF80_to_ui32.c
    ${SOFTFLOAT_SRC}/extF80_to_ui64.c
    ${SOFTFLOAT_SRC}/extF80_to_i32.c
    ${SOFTFLOAT_SRC}/extF80_to_i64.c
    ${SOFTFLOAT_SRC}/extF80_to_ui32_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80_to_ui64_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80_to_i32_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80_to_i64_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80_to_f16.c
    ${SOFTFLOAT_SRC}/extF80_to_f32.c
    ${SOFTFLOAT_SRC}/extF80_to_f64.c
    ${SOFTFLOAT_SRC}/extF80_to_f128.c
    ${SOFTFLOAT_SRC}/extF80_roundToInt.c
    ${SOFTFLOAT_SRC}/extF80_add.c
    ${SOFTFLOAT_SRC}/extF80_sub.c
    ${SOFTFLOAT_SRC}/extF80_mul.c
    ${SOFTFLOAT_SRC}/extF80_div.c
    ${SOFTFLOAT_SRC}/extF80_rem.c
    ${SOFTFLOAT_SRC}/extF80_sqrt.c
    ${SOFTFLOAT_SRC}/extF80_eq.c
    ${SOFTFLOAT_SRC}/extF80_le.c
    ${SOFTFLOAT_SRC}/extF80_lt.c
    ${SOFTFLOAT_SRC}/extF80_eq_signaling.c
    ${SOFTFLOAT_SRC}/extF80_le_quiet.c
    ${SOFTFLOAT_SRC}/extF80_lt_quiet.c
    ${SOFTFLOAT_SRC}/extF80_isSignalingNaN.c
    ${SOFTFLOAT_SRC}/extF80M_to_ui32.c
    ${SOFTFLOAT_SRC}/extF80M_to_ui64.c
    ${SOFTFLOAT_SRC}/extF80M_to_i32.c
    ${SOFTFLOAT_SRC}/extF80M_to_i64.c
    ${SOFTFLOAT_SRC}/extF80M_to_ui32_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80M_to_ui64_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80M_to_i32_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80M_to_i64_r_minMag.c
    ${SOFTFLOAT_SRC}/extF80M_to_f16.c
    ${SOFTFLOAT_SRC}/extF80M_to_f32.c
    ${SOFTFLOAT_SRC}/extF80M_to_f64.c
    ${SOFTFLOAT_SRC}/extF80M_to_f128M.c
    ${SOFTFLOAT_SRC}/extF80M_roundToInt.c
    ${SOFTFLOAT_SRC}/extF80M_add.c
    ${SOFTFLOAT_SRC}/extF80M_sub.c
    ${SOFTFLOAT_SRC}/extF80M_mul.c
    ${SOFTFLOAT_SRC}/extF80M_div.c
    ${SOFTFLOAT_SRC}/extF80M_rem.c
    ${SOFTFLOAT_SRC}/extF80M_sqrt.c
    ${SOFTFLOAT_SRC}/extF80M_eq.c
    ${SOFTFLOAT_SRC}/extF80M_le.c
    ${SOFTFLOAT_SRC}/extF80M_lt.c
    ${SOFTFLOAT_SRC}/extF80M_eq_signaling.c
    ${SOFTFLOAT_SRC}/extF80M_le_quiet.c
    ${SOFTFLOAT_SRC}/extF80M_lt_quiet.c
    ${SOFTFLOAT_SRC}/f128_to_ui32.c
    ${SOFTFLOAT_SRC}/f128_to_ui64.c
    ${SOFTFLOAT_SRC}/f128_to_i32.c
    ${SOFTFLOAT_SRC}/f128_to_i64.c
    ${SOFTFLOAT_SRC}/f128_to_ui32_r_minMag.c
    ${SOFTFLOAT_SRC}/f128_to_ui64_r_minMag.c
    ${SOFTFLOAT_SRC}/f128_to_i32_r_minMag.c
    ${SOFTFLOAT_SRC}/f128_to_i64_r_minMag.c
    ${SOFTFLOAT_SRC}/f128_to_f16.c
    ${SOFTFLOAT_SRC}/f128_to_f32.c
    ${SOFTFLOAT_SRC}/f128_to_extF80.c
    ${SOFTFLOAT_SRC}/f128_to_f64.c
    ${SOFTFLOAT_SRC}/f128_roundToInt.c
    ${SOFTFLOAT_SRC}/f128_add.c
    ${SOFTFLOAT_SRC}/f128_sub.c
    ${SOFTFLOAT_SRC}/f128_mul.c
    ${SOFTFLOAT_SRC}/f128_mulAdd.c
    ${SOFTFLOAT_SRC}/f128_div.c
    ${SOFTFLOAT_SRC}/f128_rem.c
    ${SOFTFLOAT_SRC}/f128_sqrt.c
    ${SOFTFLOAT_SRC}/f128_eq.c
    ${SOFTFLOAT_SRC}/f128_le.c
    ${SOFTFLOAT_SRC}/f128_lt.c
    ${SOFTFLOAT_SRC}/f128_eq_signaling.c
    ${SOFTFLOAT_SRC}/f128_le_quiet.c
    ${SOFTFLOAT_SRC}/f128_lt_quiet.c
    ${SOFTFLOAT_SRC}/f128_isSignalingNaN.c
    ${SOFTFLOAT_SRC}/f128M_to_ui32.c
    ${SOFTFLOAT_SRC}/f128M_to_ui64.c
    ${SOFTFLOAT_SRC}/f128M_to_i32.c
    ${SOFTFLOAT_SRC}/f128M_to_i64.c
    ${SOFTFLOAT_SRC}/f128M_to_ui32_r_minMag.c
    ${SOFTFLOAT_SRC}/f128M_to_ui64_r_minMag.c
    ${SOFTFLOAT_SRC}/f128M_to_i32_r_minMag.c
    ${SOFTFLOAT_SRC}/f128M_to_i64_r_minMag.c
    ${SOFTFLOAT_SRC}/f128M_to_f16.c
    ${SOFTFLOAT_SRC}/f128M_to_f32.c
    ${SOFTFLOAT_SRC}/f128M_to_extF80M.c
    ${SOFTFLOAT_SRC}/f128M_to_f64.c
    ${SOFTFLOAT_SRC}/f128M_roundToInt.c
    ${SOFTFLOAT_SRC}/f128M_add.c
    ${SOFTFLOAT_SRC}/f128M_sub.c
    ${SOFTFLOAT_SRC}/f128M_mul.c
    ${SOFTFLOAT_SRC}/f128M_mulAdd.c
    ${SOFTFLOAT_SRC}/f128M_div.c
    ${SOFTFLOAT_SRC}/f128M_rem.c
    ${SOFTFLOAT_SRC}/f128M_sqrt.c
    ${SOFTFLOAT_SRC}/f128M_eq.c
    ${SOFTFLOAT_SRC}/f128M_le.c
    ${SOFTFLOAT_SRC}/f128M_lt.c
    ${SOFTFLOAT_SRC}/f128M_eq_signaling.c
    ${SOFTFLOAT_SRC}/f128M_le_quiet.c
    ${SOFTFLOAT_SRC}/f128M_lt_quiet.c)

add_library(softfloat STATIC ${softfloat_sources})
target_compile_definitions(
   softfloat PUBLIC
   "-DSOFTFLOAT_FAST_INT64 -DSOFTFLOAT_ROUND_EVEN -DINLINE_LEVEL=5 -DSOFTFLOAT_FAST_DIV32TO16 -DSOFTFLOAT_FAST_DIV64TO32"
   )
target_include_directories(softfloat
                           PUBLIC ${SOFTFLOAT_SRC}/include ${SOFTFLOAT_SRC}/8086-SSE
                                  ${SOFTFLOAT_BUILD}/Linux-x86_64-GCC)
