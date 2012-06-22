/**
 * A context unit is a collection of semantic simulare assets of a web-page 
 * It contains a "entry-point" document_unit, witch can be defined that way or the document
 * with the most incoming graph vectors
*/
typedef struct context_unit{
  struct document_unit *entry_point; //entry point document_unit
  int number_of_units; //number of document units links in this context unit

  /*METHODE'S*/
  /*********************************************************/
  /* does a check to see if a document_unit with a certain */
  /* path exist in the file graph. 			   */
  /* return value:					   */
  /* 0 for succes					   */
  /* -1 for error					   */
  /*********************************************************/
  int (*fp_exist_element)(char *path,struct context_unit *); 
  void (*fp_enumerate_file_graph)(struct context_unit*);

} context_unit;

/**
 * A document_unit is a abstraction of the notion of a document, most documents
 * have a dependency list, a document_unit can not be in a non-text based format.
*/
typedef struct document_unit{
  FILE *file_handler; //the file handler for this file

  struct document_unit* links; //a list of links to other document_unit's.
  struct dependency* dependency_list; //a list of assets to complete this document.

  int number_of_links; //number of links to other document_unit's.
  int number_of_dependency; //number of dependency this document_unit has.
  char *path; //location of document_unit relative to root
} document_unit;

/**
 * A dependency is something that a document_unit needs to construct the full document.
*/
typedef struct dependency{
  FILE *file_handler;
} dependency;


/**
 * A non-text based file. Can be part of a incoming graph vector
 * or can be part of a context
*/
typedef struct opic_block{
  FILE *file_handler;
} opic_block;


/**
   The graph itself
*/
typedef struct document_graph{
} document_graph;


int exist_element(char *,struct context_unit*);
void enumerate_file_graph(struct context_unit*);
