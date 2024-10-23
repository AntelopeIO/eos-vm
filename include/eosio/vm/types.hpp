#pragma once

/*
 * definitions from https://github.com/WebAssembly/design/blob/master/BinaryEncoding.md
 */

#include <eosio/vm/allocator.hpp>
#include <eosio/vm/guarded_ptr.hpp>
#include <eosio/vm/opcodes.hpp>
#include <eosio/vm/vector.hpp>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string_view>
#include <vector>

namespace eosio { namespace vm {
   enum types { i32 = 0x7f, i64 = 0x7e, f32 = 0x7d, f64 = 0x7c, anyfunc = 0x70, func = 0x60, pseudo = 0x40, ret_void };

   enum external_kind { Function = 0, Table = 1, Memory = 2, Global = 3 };

   typedef uint8_t value_type;
   typedef uint8_t block_type;
   typedef uint8_t elem_type;

   template <typename T>
   using guarded_vector = managed_vector<T, growable_allocator>;

   struct activation_frame {
      opcode* pc;
      uint32_t last_op_index;
   };

   struct resizable_limits {
      bool     flags;
      uint32_t initial;
      uint32_t maximum = 0;
   };

   struct func_type {
      value_type                 form; // value for the func type constructor
      guarded_vector<value_type> param_types;
      uint8_t                    return_count;
      value_type                 return_type;
   };

   inline bool operator==(const func_type& lhs, const func_type& rhs) {
      return lhs.form == rhs.form &&
        lhs.param_types.size() == rhs.param_types.size() &&
        std::equal(lhs.param_types.raw(), lhs.param_types.raw() + lhs.param_types.size(), rhs.param_types.raw()) &&
        lhs.return_count == rhs.return_count &&
        (lhs.return_count || lhs.return_type == rhs.return_type);
   }

   union expr_value {
      int32_t  i32;
      int64_t  i64;
      uint32_t f32;
      uint64_t f64;
   };

   struct init_expr {
      int8_t     opcode;
      expr_value value;
   };

   struct global_type {
      value_type content_type;
      bool       mutability;
   };

   struct global_variable {
      global_type type;
      init_expr   init;
   };

   struct table_type {
      elem_type                element_type;
      resizable_limits         limits;
      guarded_vector<uint32_t> table;
   };

   struct memory_type {
      resizable_limits limits;
   };

   union import_type {
      import_type() {}
      uint32_t    func_t;
      table_type  table_t;
      memory_type mem_t;
      global_type global_t;
   };

   struct import_entry {
      guarded_vector<uint8_t> module_str;
      guarded_vector<uint8_t> field_str;
      external_kind           kind;
      import_type             type;
   };

   struct export_entry {
      guarded_vector<uint8_t> field_str;
      external_kind           kind;
      uint32_t                index;
   };

   struct elem_segment {
      uint32_t                 index;
      init_expr                offset;
      guarded_vector<uint32_t> elems;
   };

   struct local_entry {
      uint32_t   count;
      value_type type;
   };

   union native_value {
      native_value() = default;
      constexpr native_value(uint32_t arg) : i32(arg) {}
      constexpr native_value(uint64_t arg) : i64(arg) {}
      constexpr native_value(float arg) : f32(arg) {}
      constexpr native_value(double arg) : f64(arg) {}
      uint32_t i32;
      uint64_t i64;
      float f32;
      double f64;
   };

   struct function_body {
      uint32_t                    size;
      guarded_vector<local_entry> locals;
      opcode*                     code;
      std::size_t                 jit_code_offset;
   };

   struct data_segment {
      uint32_t                index;
      init_expr               offset;
      guarded_vector<uint8_t> data;
   };

   using wasm_code     = std::vector<uint8_t>;
   using wasm_code_ptr = guarded_ptr<uint8_t>;
   typedef std::uint32_t  wasm_ptr_t;
   typedef std::uint32_t  wasm_size_t;

   struct name_assoc {
      std::uint32_t idx;
      guarded_vector<uint8_t> name;
   };
   struct indirect_name_assoc {
      std::uint32_t idx;
      guarded_vector<name_assoc> namemap;
   };
   struct name_section {
      guarded_vector<uint8_t>* module_name = nullptr;
      guarded_vector<name_assoc>* function_names = nullptr;
      guarded_vector<indirect_name_assoc>* local_names = nullptr;
   };

   struct module {
      growable_allocator              allocator;
      uint32_t                        start     = std::numeric_limits<uint32_t>::max();
      guarded_vector<func_type>       types     = { allocator, 0 };
      guarded_vector<import_entry>    imports   = { allocator, 0 };
      guarded_vector<uint32_t>        functions = { allocator, 0 };
      guarded_vector<table_type>      tables    = { allocator, 0 };
      guarded_vector<memory_type>     memories  = { allocator, 0 };
      guarded_vector<global_variable> globals   = { allocator, 0 };
      guarded_vector<export_entry>    exports   = { allocator, 0 };
      guarded_vector<elem_segment>    elements  = { allocator, 0 };
      guarded_vector<function_body>   code      = { allocator, 0 };
      guarded_vector<data_segment>    data      = { allocator, 0 };

      // Custom sections:
      name_section* names = nullptr;

      // not part of the spec for WASM
      guarded_vector<uint32_t> import_functions = { allocator, 0 };
      guarded_vector<uint32_t> type_aliases     = { allocator, 0 };
      guarded_vector<uint32_t> fast_functions   = { allocator, 0 };
      uint64_t                 maximum_stack    = 0;
      // If non-null, indicates that the parser encountered an error
      // that would prevent successful instantiation.  Must refer
      // to memory with static storage duration.
      const char *             error            = nullptr;

      // Stores data needed by JIT execution, in memory managed by standard
      // C++ vectors, not growable_allocator used by guarded_vector,
      // such that growable_allocator can be released after parsing.
      // All growable_allocators (including recursively) used in module
      // are redefined by std::vector in jit_mod_t.
      // This is to make it possible parsing WASM only once for JIT.
      struct jit_mod_t {
         struct jit_func_type {
            value_type                 form;
            std::vector<value_type>    param_types;
            uint8_t                    return_count;
            value_type                 return_type;
         };
         struct jit_import_type {
            uint32_t    func_t;
         };
         struct jit_import_entry {
            std::vector<uint8_t> module_str;
            std::vector<uint8_t> field_str;
            external_kind        kind;
            jit_import_type      type;
         };
         struct jit_export_entry {
            std::vector<uint8_t> field_str;
            external_kind        kind;
            uint32_t             index;
         };
         struct jit_data_segment {
            uint32_t              index;
            init_expr             offset;
            std::vector<uint8_t>  data;
         };

         std::vector<jit_func_type>        types;
         std::vector<jit_import_entry>     imports;
         std::vector<uint32_t>             functions;
         // tables not needed during JIT execution
         std::vector<memory_type>          memories;
         std::vector<global_variable>      globals;
         std::vector<jit_export_entry>     exports;
         // elements not needed during JIT execution
         std::vector<size_t>               jit_code_offset;
         std::vector<jit_data_segment>     data;
         std::vector<uint32_t>             import_functions;
         // type_aliases and fast_functions not needed during JIT execution

         auto& get_function_type(uint32_t index) const {
            if (index < get_imported_functions_size())
               return types[imports[index].type.func_t];
            return types[functions[index - get_imported_functions_size()]];
         }
         uint32_t get_imported_functions_size() const {
            return get_imported_functions_size_impl(imports);
         }
      };

      // The memory storing module data for JIT
      std::unique_ptr<jit_mod_t> jit_mod;

      // Constructs data for JIT execution.
      // Called from backend::construct() after parsing is finalized.
      void make_jit_module() {
         jit_mod = std::make_unique<jit_mod_t>();

         if (auto types_size = types.size(); types_size > 0) {
            jit_mod->types.reserve(types_size);
            for (uint32_t i = 0; i < types_size; ++i) {
               const auto& type = types[i];
               jit_mod->types.emplace_back(jit_mod_t::jit_func_type{
                  type.form,
                  {type.param_types.data(), type.param_types.data() + type.param_types.size()},
                  type.return_count,
                  type.return_type
               });
            }
         }

         if (auto imports_size = imports.size(); imports_size > 0) {
            jit_mod->imports.reserve(imports_size);
            for (uint32_t i = 0; i < imports_size; ++i) {
               const auto& entry = imports[i];
               jit_mod->imports.emplace_back(jit_mod_t::jit_import_entry{
                  {entry.module_str.data(), entry.module_str.data() + entry.module_str.size()},
                  {entry.field_str.data(), entry.field_str.data() + entry.field_str.size()},
                  entry.kind,
                  {entry.type.func_t}
               });
            }
         }

         if (memories.size() > 0) {
            jit_mod->memories.emplace_back(memories[0]); // memories has one element only
         }

         if (functions.size() > 0) {
            jit_mod->functions.assign(functions.data(), functions.data() + functions.size());
         }

         if (globals.size() > 0) {
            jit_mod->globals.assign(globals.raw(), globals.raw() + globals.size());
         }

         if (auto exports_size = exports.size(); exports_size > 0) {
            jit_mod->exports.reserve(exports_size);
            for (uint32_t i = 0; i < exports_size; ++i) {
               const auto& entry = exports[i];
               jit_mod->exports.emplace_back(jit_mod_t::jit_export_entry{
                  {entry.field_str.data(), entry.field_str.data() + entry.field_str.size()},
                  entry.kind,
                  entry.index
               });
            }
         }

         if (auto code_size = code.size(); code_size > 0) {
            jit_mod->jit_code_offset.reserve(code_size);
            for (uint32_t i = 0; i < code_size; ++i) {
               jit_mod->jit_code_offset.emplace_back(code[i].jit_code_offset);
            }
         }

         if (auto data_size = data.size(); data_size > 0) {
            jit_mod->data.reserve(data_size);
            for (uint32_t i = 0; i < data_size; ++i) {
               const auto& data_seg = data[i];
               jit_mod->data.emplace_back(jit_mod_t::jit_data_segment{
                  data_seg.index,
                  data_seg.offset,
                  {data_seg.data.data(), data_seg.data.data() + data_seg.data.size()}
               });
            }
         }

         if (import_functions.size() > 0) {
            jit_mod->import_functions.assign(import_functions.data(), import_functions.data() + import_functions.size());
         }
      }

      void finalize() {
         import_functions.resize(get_imported_functions_size());
         allocator.finalize();
      }
      uint32_t get_imported_functions_size() const {
         return get_imported_functions_size_impl(imports);
      }
      template<typename Imports>
      static uint32_t get_imported_functions_size_impl(const Imports& imports) {
         uint32_t number_of_imports = 0;
         const auto sz = imports.size();
         // we don't want to use `imports[i]` or `imports.at(i)` since these do an unnecessary check
         // `EOS_VM_ASSERT(i < _size)`. The check is unnecessary since we iterate from `0` to `_size`.
         // So get the pointer to the first element and dereference it directly.
         // ------------------------------------------------------------------------------------------------
         const auto data = imports.data();
         for (uint32_t i = 0; i < sz; i++) {
            if (data[i].kind == external_kind::Function)
               number_of_imports++;
         }
         return number_of_imports;
      }
      inline uint32_t get_functions_size() const { return functions.size(); }
      inline uint32_t get_functions_total() const { return get_imported_functions_size() + get_functions_size(); }
      inline opcode* get_function_pc( uint32_t fidx ) const {
         EOS_VM_ASSERT( fidx >= get_imported_functions_size(), wasm_interpreter_exception, "trying to get the PC of an imported function" );
         return code[fidx-get_imported_functions_size()].code;
      }

      inline auto& get_opcode(uint32_t pc) const {
         return ((opcode*)&code[0].code[0])[pc];
      }

      inline uint32_t get_function_locals_size(uint32_t index) const {
         EOS_VM_ASSERT(index >= get_imported_functions_size(), wasm_interpreter_exception, "imported functions do not have locals");
         return code[index - get_imported_functions_size()].locals.size();
      }

      auto& get_function_type(uint32_t index) const {
         if (index < get_imported_functions_size())
            return types[imports[index].type.func_t];
         return types[functions[index - get_imported_functions_size()]];
      }

      // When jit_mod is available, this function executes on jit_mod,
      // otherwise on module itself.
      uint32_t get_exported_function(const std::string_view str) {
         return (jit_mod) ? get_exported_function_impl(jit_mod->exports, str) : get_exported_function_impl(exports, str);
      }

      template<typename Exports>
      static uint32_t get_exported_function_impl(const Exports& exports, const std::string_view str) {
         uint32_t index = std::numeric_limits<uint32_t>::max();
         for (uint32_t i = 0; i < exports.size(); i++) {
            if (exports[i].kind == external_kind::Function && exports[i].field_str.size() == str.size() &&
                memcmp((const char*)str.data(), (const char*)exports[i].field_str.data(), exports[i].field_str.size()) ==
                      0) {
               index = exports[i].index;
               break;
            }
         }
         return index;
      }

      void normalize_types() {
         type_aliases.resize(types.size());
         for (uint32_t i = 0; i < types.size(); ++i) {
            uint32_t j = 0;
            for (; j < i; ++j) {
               if (types[j] == types[i]) {
                  break;
               }
            }
            type_aliases[i] = j;
         }

         uint32_t imported_functions_size = get_imported_functions_size();
         fast_functions.resize(functions.size() + imported_functions_size);
         for (uint32_t i = 0; i < imported_functions_size; ++i) {
            fast_functions[i] = type_aliases[imports[i].type.func_t];
         }
         for (uint32_t i = 0; i < functions.size(); ++i) {
            fast_functions[i + imported_functions_size] = type_aliases[functions[i]];
         }
      }
   };
}} // namespace eosio::vm
