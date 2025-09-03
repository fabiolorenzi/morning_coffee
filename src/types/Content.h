#pragma once

#include <QString>

struct Content {
    int id;
    int sourceId;
    QString title;
    QString url;
    QString fingerprint;

    bool operator!=(const Content& other) const {
        return fingerprint != other.fingerprint;
    }
};