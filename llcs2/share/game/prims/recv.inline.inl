#pragma once

namespace game {
  inline void RecvTable::for_each_node( const std::function<bool( Node * )> &closure ) {
    for ( std::size_t i{}; i < _size; i++ ) {
      if ( closure( &_nodes[ i ] ) ) {
        return;
      }
    }
  }

  inline void RecvTable::for_each_node( const std::function<bool( const Node * )> &closure ) const {
    for ( std::size_t i{}; i < _size; i++ ) {
      if ( closure( &_nodes[ i ] ) ) {
        return;
      }
    }
  }

  inline RecvTable::Node *RecvTable::find( const std::string_view name ) {
    if ( name.empty( ) ) {
      return nullptr;
    }

    for ( std::size_t i{}; i < _size; i++ ) {
      if ( name.find( _nodes[ i ]._name ) != name.npos ) {
        return &_nodes[ i ];
      }
    }

    return nullptr;
  }

  inline const RecvTable::Node *RecvTable::find( const std::string_view name ) const {
    if ( name.empty( ) ) {
      return nullptr;
    }

    for ( std::size_t i{}; i < _size; i++ ) {
      if ( name.find( _nodes[ i ]._name ) != name.npos ) {
        return &_nodes[ i ];
      }
    }

    return nullptr;
  }

  inline void RecvTable::dump( std::ostream &stream ) const {
    for_each_node(
      [ &stream ]( const Node *node ) {
        stream << "node found!" << std::endl;
        stream << " name: " << node->_name << std::endl;
        stream << " offset: " << node->_offset << std::endl;
        stream << " flags: " << node->_flags << std::endl;
        stream << " send type: " << node->_send_type << std::endl;
        stream << std::endl;

        return false;
      }
    );
  }
}