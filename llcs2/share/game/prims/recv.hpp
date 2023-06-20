#pragma once

namespace game {
	/* recv table encapsulates an array of the fields (and their layout info)
	   being sent via a net channel by a client and retrieved by a server for
		 the multiplayer sake. these fields can be exploited for many things, such as
		 getting the field info of networked classes, finding member offsets, etc...*/
	struct RecvTable {
		struct Node {
      char            *_name{};
      int             _send_type{};
      int             _flags{};
      int             _buf_size{};
      bool            _in_arr{};
      Address         _extras{};
      Node             *_arr_prop{};
      Address         _arr_len_proxy{};
      Address         _proxy_fn{};
      Address         _table_proxy_fn{};
      RecvTable       *_table{};
      std::uint32_t   _offset{};
      int             _stride{};
      int             _elements{};
      char            *_parent_arr_prop_name{};

      inline constexpr Node( ) = default;
		};

    Node              *_nodes{};
    int               _size{};
    void              *_decoder{};
    const char        *_name{};
    bool              _initialized{};
    bool              _in_main_list{};

    inline constexpr RecvTable( ) = default;

    inline void for_each_node( const std::function<bool( Node * )> &closure );

    inline void for_each_node( const std::function<bool( const Node * )> &closure ) const;

    inline Node *find( const std::string_view name );

    inline const Node *find( const std::string_view name ) const;

    inline void dump( std::ostream &stream ) const;
	};
}

#include "recv.inline.inl"