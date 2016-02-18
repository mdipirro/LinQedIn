#ifndef SEARCHBYSURNAME_H
#define SEARCHBYSURNAME_H

#include "searchfunctor.h"
#include <QString>

class SearchBySurname:virtual public SearchFunctor{
        private:
            QString surname;

        public:
            SearchBySurname(const QString&);
            bool operator()(const SmartUser&) const;
};

#endif // SEARCHBYSURNAME_H
