#ifndef SEARCHRESULTS_H
#define SEARCHRESULTS_H

#include "user/user.h"
#include "user/smartuser.h"
#include "permissions.h"
#include "user/profileinformations/personal.h"
#include <QVector>
#include <QString>

/* La classe fornisce un'astrazione e un livello superiore alle classi contenitore di Qt. Vengono forniti dei metodi per
 * iterare sui risultati senza poterli modificare (const_iterator). La classe non fornisce alcun metodo di rappresentazione
 * dei dati che contiene: l'utilizzatore della classe fornirà opportuni metodi per rappresentare i dati.
 */
class SearchResults{
    friend class ScanResults;
public:
    class Result{ //astrazione di SmartUser per impedire l'accesso ad informazioni vietate
    private:
        QString username,name,surname,actualJob;
        Personal::Genders gender;
        bool visibleProfile,visibleNetwork;
    public:
        explicit Result(const QString& ="",const QString& ="",const QString& ="",const QString& ="",
                        Personal::Genders =Personal::M,
                        bool =false,bool =false);
        enum ViewPermits{profile,network};
        QString getUsername() const;
        QString getName() const;
        QString getSurname() const;
        QString getActualJob() const;
        Personal::Genders getGender() const;
        bool isAbleTo(ViewPermits) const;
    };

    class ScanResults{
        friend class SearchResults;
    private:
        QVector<Result>::const_iterator it;
        ScanResults(const QVector<Result>::const_iterator&);
    public:
        ScanResults operator++();
        ScanResults& operator++(int);
        ScanResults& operator+(int);
        bool operator==(const ScanResults&) const;
        bool operator!=(const ScanResults&) const;
        Result operator*() const;
    };

    explicit SearchResults(const QVector<Result>& =QVector<Result>());
    void addResult(const Result&);
    ScanResults begin() const;
    ScanResults end() const;
    int size() const;

private:
    QVector<Result> results;
};

#endif // SEARCHRESULTS_H
