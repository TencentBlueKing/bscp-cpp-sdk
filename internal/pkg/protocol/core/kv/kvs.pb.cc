// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pkg/protocol/core/kv/kvs.proto

#include "pkg/protocol/core/kv/kvs.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace pbkv {
constexpr Kv::Kv(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : kv_state_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , spec_(nullptr)
  , attachment_(nullptr)
  , revision_(nullptr)
  , id_(0u){}
struct KvDefaultTypeInternal {
  constexpr KvDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~KvDefaultTypeInternal() {}
  union {
    Kv _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT KvDefaultTypeInternal _Kv_default_instance_;
constexpr KvSpec::KvSpec(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : key_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , kv_type_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , value_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct KvSpecDefaultTypeInternal {
  constexpr KvSpecDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~KvSpecDefaultTypeInternal() {}
  union {
    KvSpec _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT KvSpecDefaultTypeInternal _KvSpec_default_instance_;
constexpr KvAttachment::KvAttachment(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : biz_id_(0u)
  , app_id_(0u){}
struct KvAttachmentDefaultTypeInternal {
  constexpr KvAttachmentDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~KvAttachmentDefaultTypeInternal() {}
  union {
    KvAttachment _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT KvAttachmentDefaultTypeInternal _KvAttachment_default_instance_;
}  // namespace pbkv
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto = nullptr;

const uint32_t TableStruct_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::pbkv::Kv, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::pbkv::Kv, id_),
  PROTOBUF_FIELD_OFFSET(::pbkv::Kv, kv_state_),
  PROTOBUF_FIELD_OFFSET(::pbkv::Kv, spec_),
  PROTOBUF_FIELD_OFFSET(::pbkv::Kv, attachment_),
  PROTOBUF_FIELD_OFFSET(::pbkv::Kv, revision_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::pbkv::KvSpec, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::pbkv::KvSpec, key_),
  PROTOBUF_FIELD_OFFSET(::pbkv::KvSpec, kv_type_),
  PROTOBUF_FIELD_OFFSET(::pbkv::KvSpec, value_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::pbkv::KvAttachment, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::pbkv::KvAttachment, biz_id_),
  PROTOBUF_FIELD_OFFSET(::pbkv::KvAttachment, app_id_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::pbkv::Kv)},
  { 11, -1, -1, sizeof(::pbkv::KvSpec)},
  { 20, -1, -1, sizeof(::pbkv::KvAttachment)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::pbkv::_Kv_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::pbkv::_KvSpec_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::pbkv::_KvAttachment_default_instance_),
};

const char descriptor_table_protodef_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\036pkg/protocol/core/kv/kvs.proto\022\004pbkv\032!"
  "pkg/protocol/core/base/base.proto\"\212\001\n\002Kv"
  "\022\n\n\002id\030\001 \001(\r\022\020\n\010kv_state\030\002 \001(\t\022\032\n\004spec\030\003"
  " \001(\0132\014.pbkv.KvSpec\022&\n\nattachment\030\004 \001(\0132\022"
  ".pbkv.KvAttachment\022\"\n\010revision\030\005 \001(\0132\020.p"
  "bbase.Revision\"5\n\006KvSpec\022\013\n\003key\030\001 \001(\t\022\017\n"
  "\007kv_type\030\002 \001(\t\022\r\n\005value\030\003 \001(\t\".\n\014KvAttac"
  "hment\022\016\n\006biz_id\030\001 \001(\r\022\016\n\006app_id\030\002 \001(\rBSZ"
  "Qgithub.com/TencentBlueKing/bk-bcs/bcs-s"
  "ervices/bcs-bscp/pkg/protocol/core/kv;pb"
  "kvb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_deps[1] = {
  &::descriptor_table_pkg_2fprotocol_2fcore_2fbase_2fbase_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto = {
  false, false, 410, descriptor_table_protodef_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto, "pkg/protocol/core/kv/kvs.proto", 
  &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_once, descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_deps, 1, 3,
  schemas, file_default_instances, TableStruct_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto::offsets,
  file_level_metadata_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto, file_level_enum_descriptors_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto, file_level_service_descriptors_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_getter() {
  return &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto(&descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto);
namespace pbkv {

// ===================================================================

class Kv::_Internal {
 public:
  static const ::pbkv::KvSpec& spec(const Kv* msg);
  static const ::pbkv::KvAttachment& attachment(const Kv* msg);
  static const ::pbbase::Revision& revision(const Kv* msg);
};

const ::pbkv::KvSpec&
Kv::_Internal::spec(const Kv* msg) {
  return *msg->spec_;
}
const ::pbkv::KvAttachment&
Kv::_Internal::attachment(const Kv* msg) {
  return *msg->attachment_;
}
const ::pbbase::Revision&
Kv::_Internal::revision(const Kv* msg) {
  return *msg->revision_;
}
void Kv::clear_revision() {
  if (GetArenaForAllocation() == nullptr && revision_ != nullptr) {
    delete revision_;
  }
  revision_ = nullptr;
}
Kv::Kv(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:pbkv.Kv)
}
Kv::Kv(const Kv& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  kv_state_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    kv_state_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_kv_state().empty()) {
    kv_state_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_kv_state(), 
      GetArenaForAllocation());
  }
  if (from._internal_has_spec()) {
    spec_ = new ::pbkv::KvSpec(*from.spec_);
  } else {
    spec_ = nullptr;
  }
  if (from._internal_has_attachment()) {
    attachment_ = new ::pbkv::KvAttachment(*from.attachment_);
  } else {
    attachment_ = nullptr;
  }
  if (from._internal_has_revision()) {
    revision_ = new ::pbbase::Revision(*from.revision_);
  } else {
    revision_ = nullptr;
  }
  id_ = from.id_;
  // @@protoc_insertion_point(copy_constructor:pbkv.Kv)
}

inline void Kv::SharedCtor() {
kv_state_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  kv_state_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&spec_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&id_) -
    reinterpret_cast<char*>(&spec_)) + sizeof(id_));
}

Kv::~Kv() {
  // @@protoc_insertion_point(destructor:pbkv.Kv)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void Kv::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  kv_state_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete spec_;
  if (this != internal_default_instance()) delete attachment_;
  if (this != internal_default_instance()) delete revision_;
}

void Kv::ArenaDtor(void* object) {
  Kv* _this = reinterpret_cast< Kv* >(object);
  (void)_this;
}
void Kv::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void Kv::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void Kv::Clear() {
// @@protoc_insertion_point(message_clear_start:pbkv.Kv)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  kv_state_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && spec_ != nullptr) {
    delete spec_;
  }
  spec_ = nullptr;
  if (GetArenaForAllocation() == nullptr && attachment_ != nullptr) {
    delete attachment_;
  }
  attachment_ = nullptr;
  if (GetArenaForAllocation() == nullptr && revision_ != nullptr) {
    delete revision_;
  }
  revision_ = nullptr;
  id_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Kv::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string kv_state = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_kv_state();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "pbkv.Kv.kv_state"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .pbkv.KvSpec spec = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_spec(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .pbkv.KvAttachment attachment = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          ptr = ctx->ParseMessage(_internal_mutable_attachment(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .pbbase.Revision revision = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          ptr = ctx->ParseMessage(_internal_mutable_revision(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Kv::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:pbkv.Kv)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_id(), target);
  }

  // string kv_state = 2;
  if (!this->_internal_kv_state().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_kv_state().data(), static_cast<int>(this->_internal_kv_state().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "pbkv.Kv.kv_state");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_kv_state(), target);
  }

  // .pbkv.KvSpec spec = 3;
  if (this->_internal_has_spec()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        3, _Internal::spec(this), target, stream);
  }

  // .pbkv.KvAttachment attachment = 4;
  if (this->_internal_has_attachment()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        4, _Internal::attachment(this), target, stream);
  }

  // .pbbase.Revision revision = 5;
  if (this->_internal_has_revision()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        5, _Internal::revision(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbkv.Kv)
  return target;
}

size_t Kv::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbkv.Kv)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string kv_state = 2;
  if (!this->_internal_kv_state().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_kv_state());
  }

  // .pbkv.KvSpec spec = 3;
  if (this->_internal_has_spec()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *spec_);
  }

  // .pbkv.KvAttachment attachment = 4;
  if (this->_internal_has_attachment()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *attachment_);
  }

  // .pbbase.Revision revision = 5;
  if (this->_internal_has_revision()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *revision_);
  }

  // uint32 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Kv::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    Kv::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Kv::GetClassData() const { return &_class_data_; }

void Kv::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<Kv *>(to)->MergeFrom(
      static_cast<const Kv &>(from));
}


void Kv::MergeFrom(const Kv& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbkv.Kv)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_kv_state().empty()) {
    _internal_set_kv_state(from._internal_kv_state());
  }
  if (from._internal_has_spec()) {
    _internal_mutable_spec()->::pbkv::KvSpec::MergeFrom(from._internal_spec());
  }
  if (from._internal_has_attachment()) {
    _internal_mutable_attachment()->::pbkv::KvAttachment::MergeFrom(from._internal_attachment());
  }
  if (from._internal_has_revision()) {
    _internal_mutable_revision()->::pbbase::Revision::MergeFrom(from._internal_revision());
  }
  if (from._internal_id() != 0) {
    _internal_set_id(from._internal_id());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Kv::CopyFrom(const Kv& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbkv.Kv)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Kv::IsInitialized() const {
  return true;
}

void Kv::InternalSwap(Kv* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &kv_state_, lhs_arena,
      &other->kv_state_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Kv, id_)
      + sizeof(Kv::id_)
      - PROTOBUF_FIELD_OFFSET(Kv, spec_)>(
          reinterpret_cast<char*>(&spec_),
          reinterpret_cast<char*>(&other->spec_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Kv::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_getter, &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_once,
      file_level_metadata_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto[0]);
}

// ===================================================================

class KvSpec::_Internal {
 public:
};

KvSpec::KvSpec(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:pbkv.KvSpec)
}
KvSpec::KvSpec(const KvSpec& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  key_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    key_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_key().empty()) {
    key_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_key(), 
      GetArenaForAllocation());
  }
  kv_type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    kv_type_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_kv_type().empty()) {
    kv_type_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_kv_type(), 
      GetArenaForAllocation());
  }
  value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    value_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_value().empty()) {
    value_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_value(), 
      GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:pbkv.KvSpec)
}

inline void KvSpec::SharedCtor() {
key_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  key_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
kv_type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  kv_type_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
value_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  value_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

KvSpec::~KvSpec() {
  // @@protoc_insertion_point(destructor:pbkv.KvSpec)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void KvSpec::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  key_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  kv_type_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  value_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void KvSpec::ArenaDtor(void* object) {
  KvSpec* _this = reinterpret_cast< KvSpec* >(object);
  (void)_this;
}
void KvSpec::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void KvSpec::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void KvSpec::Clear() {
// @@protoc_insertion_point(message_clear_start:pbkv.KvSpec)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  key_.ClearToEmpty();
  kv_type_.ClearToEmpty();
  value_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* KvSpec::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string key = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_key();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "pbkv.KvSpec.key"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string kv_type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_kv_type();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "pbkv.KvSpec.kv_type"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string value = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_value();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "pbkv.KvSpec.value"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* KvSpec::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:pbkv.KvSpec)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string key = 1;
  if (!this->_internal_key().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_key().data(), static_cast<int>(this->_internal_key().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "pbkv.KvSpec.key");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_key(), target);
  }

  // string kv_type = 2;
  if (!this->_internal_kv_type().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_kv_type().data(), static_cast<int>(this->_internal_kv_type().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "pbkv.KvSpec.kv_type");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_kv_type(), target);
  }

  // string value = 3;
  if (!this->_internal_value().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_value().data(), static_cast<int>(this->_internal_value().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "pbkv.KvSpec.value");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_value(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbkv.KvSpec)
  return target;
}

size_t KvSpec::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbkv.KvSpec)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string key = 1;
  if (!this->_internal_key().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_key());
  }

  // string kv_type = 2;
  if (!this->_internal_kv_type().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_kv_type());
  }

  // string value = 3;
  if (!this->_internal_value().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_value());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData KvSpec::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    KvSpec::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*KvSpec::GetClassData() const { return &_class_data_; }

void KvSpec::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<KvSpec *>(to)->MergeFrom(
      static_cast<const KvSpec &>(from));
}


void KvSpec::MergeFrom(const KvSpec& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbkv.KvSpec)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_key().empty()) {
    _internal_set_key(from._internal_key());
  }
  if (!from._internal_kv_type().empty()) {
    _internal_set_kv_type(from._internal_kv_type());
  }
  if (!from._internal_value().empty()) {
    _internal_set_value(from._internal_value());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void KvSpec::CopyFrom(const KvSpec& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbkv.KvSpec)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KvSpec::IsInitialized() const {
  return true;
}

void KvSpec::InternalSwap(KvSpec* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &key_, lhs_arena,
      &other->key_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &kv_type_, lhs_arena,
      &other->kv_type_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &value_, lhs_arena,
      &other->value_, rhs_arena
  );
}

::PROTOBUF_NAMESPACE_ID::Metadata KvSpec::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_getter, &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_once,
      file_level_metadata_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto[1]);
}

// ===================================================================

class KvAttachment::_Internal {
 public:
};

KvAttachment::KvAttachment(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:pbkv.KvAttachment)
}
KvAttachment::KvAttachment(const KvAttachment& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&biz_id_, &from.biz_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&app_id_) -
    reinterpret_cast<char*>(&biz_id_)) + sizeof(app_id_));
  // @@protoc_insertion_point(copy_constructor:pbkv.KvAttachment)
}

inline void KvAttachment::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&biz_id_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&app_id_) -
    reinterpret_cast<char*>(&biz_id_)) + sizeof(app_id_));
}

KvAttachment::~KvAttachment() {
  // @@protoc_insertion_point(destructor:pbkv.KvAttachment)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void KvAttachment::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void KvAttachment::ArenaDtor(void* object) {
  KvAttachment* _this = reinterpret_cast< KvAttachment* >(object);
  (void)_this;
}
void KvAttachment::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void KvAttachment::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void KvAttachment::Clear() {
// @@protoc_insertion_point(message_clear_start:pbkv.KvAttachment)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&biz_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&app_id_) -
      reinterpret_cast<char*>(&biz_id_)) + sizeof(app_id_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* KvAttachment::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 biz_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          biz_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // uint32 app_id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          app_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* KvAttachment::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:pbkv.KvAttachment)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 biz_id = 1;
  if (this->_internal_biz_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(1, this->_internal_biz_id(), target);
  }

  // uint32 app_id = 2;
  if (this->_internal_app_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt32ToArray(2, this->_internal_app_id(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:pbkv.KvAttachment)
  return target;
}

size_t KvAttachment::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:pbkv.KvAttachment)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // uint32 biz_id = 1;
  if (this->_internal_biz_id() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_biz_id());
  }

  // uint32 app_id = 2;
  if (this->_internal_app_id() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt32SizePlusOne(this->_internal_app_id());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData KvAttachment::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    KvAttachment::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*KvAttachment::GetClassData() const { return &_class_data_; }

void KvAttachment::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<KvAttachment *>(to)->MergeFrom(
      static_cast<const KvAttachment &>(from));
}


void KvAttachment::MergeFrom(const KvAttachment& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:pbkv.KvAttachment)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_biz_id() != 0) {
    _internal_set_biz_id(from._internal_biz_id());
  }
  if (from._internal_app_id() != 0) {
    _internal_set_app_id(from._internal_app_id());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void KvAttachment::CopyFrom(const KvAttachment& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:pbkv.KvAttachment)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool KvAttachment::IsInitialized() const {
  return true;
}

void KvAttachment::InternalSwap(KvAttachment* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(KvAttachment, app_id_)
      + sizeof(KvAttachment::app_id_)
      - PROTOBUF_FIELD_OFFSET(KvAttachment, biz_id_)>(
          reinterpret_cast<char*>(&biz_id_),
          reinterpret_cast<char*>(&other->biz_id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata KvAttachment::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_getter, &descriptor_table_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto_once,
      file_level_metadata_pkg_2fprotocol_2fcore_2fkv_2fkvs_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace pbkv
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::pbkv::Kv* Arena::CreateMaybeMessage< ::pbkv::Kv >(Arena* arena) {
  return Arena::CreateMessageInternal< ::pbkv::Kv >(arena);
}
template<> PROTOBUF_NOINLINE ::pbkv::KvSpec* Arena::CreateMaybeMessage< ::pbkv::KvSpec >(Arena* arena) {
  return Arena::CreateMessageInternal< ::pbkv::KvSpec >(arena);
}
template<> PROTOBUF_NOINLINE ::pbkv::KvAttachment* Arena::CreateMaybeMessage< ::pbkv::KvAttachment >(Arena* arena) {
  return Arena::CreateMessageInternal< ::pbkv::KvAttachment >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
