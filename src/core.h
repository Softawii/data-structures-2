//
// Created by yancf on 02/07/2022.
//

#ifndef REPLACEMENTSELECTION_CORE_H
#define REPLACEMENTSELECTION_CORE_H

typedef void * var;
typedef var  (from_stream)(FILE *);
typedef void (to_stream)  (FILE *, var);
typedef int  (comparator) (var, var);
typedef void (show)       (var);



#endif //REPLACEMENTSELECTION_CORE_H
