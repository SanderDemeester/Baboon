/**
 * A context unit is a collection of semantic simulare assets of a web-page 
 * It contains a "entry-point" document_unit, witch can be defined that way or the document
 * with the most incoming graph vectors
*/
typedef struct context_unit{
};

/**
 * A document_unit is a abstraction of the notion of a document, most documents
 * have a dependency list, a document_unit can not be in a non-text based format.
*/
typedef struct document_unit{
  FILE *file_handler; //the file handler for this file

  struct document_unit* links; //a list of links to other document_unit's.
  struct dependency* dependency_list; //a list of assets to complete this document.

  int number_of_links; //number of links to other document_unit's.
  int number_of_dependency //number of dependency this document_unit has.
  
  
};

/**
 * A dependency is something that a document_unit needs to construct the full document.
*/
typedef struct dependency{
};


/**
 * A non-text based file. Can be part of a incoming graph vector
 * or can be part of a context
*/
typedef struct opic_block{
};
