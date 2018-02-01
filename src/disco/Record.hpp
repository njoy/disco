template < typename... Components >
struct Record;

template<>
struct Record<> {

  template< typename Iterator >
  static void read( Iterator& it, const Iterator& end ){
    auto foundEndOfRecord = [&it](){
      return ( FixedWidthField< 0 >::isNewline( *it, it )
               or FixedWidthField< 0 >::isEOF( *it ) );
    };
    while ( it != end and not foundEndOfRecord() ){ ++it; }
    std::advance( it,
                  FixedWidthField< 0 >::isNewline( *it, it ) and it != end );
  }

  template< typename Iterator, typename... Args >
  static void write( Iterator& it, const Args&... ){
    *it++='\n';
  }

};

template<>
struct Record< RetainCarriage > {

  template< typename Iterator >
  static void read( Iterator&, const Iterator& ){}

  template< typename Iterator, typename... Args >
  static void write( Iterator&, const Args&... ){}

};

template< uint16_t w, typename... Components >
struct Record< ColumnPosition< w >, Components... > {

  template< typename Iterator, typename... Args >
  static void read( Iterator& it, const Iterator& end, Args&... args ){
    ColumnPosition< w >::read( it, end );
    Record< Components... >::read( it, end, args... );
  }

  template< typename Iterator, typename... Args >
  static void write( Iterator& it, const Args&... args ){
    ColumnPosition< w >::write( it );
    Record< Components... >::write( it, args... );
  }

};

template< typename Component, typename... Components >
struct Record< Component, Components... > {

  using Subrecord =  Record< Components... >;

  template< typename Iterator >
  static void read( Iterator& it, const Iterator& end ){
    Component::read( it, end );
    Subrecord::read( it, end );
  }

  template< typename Iterator, typename SinkType, typename... Args >
  static void read( Iterator& it, const Iterator& end, SinkType& sink, Args&... args ){
    sink = Component::template read< SinkType >( it, end );
    Subrecord::read( it, end, args... );
  }

  template< typename Iterator >
  static void write( Iterator& it ){
    Component::write( it );
    Subrecord::write( it );
  }

  template< typename Iterator, typename SourceType, typename... Args >
  static void write( Iterator& it, const SourceType& source, const Args&... args ){
    Component::write( source, it );
    Subrecord::write( it, args... );
  }

};
