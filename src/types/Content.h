#pragma once

#include <QString>

struct Content {
    int id;
    int sourceId;
    QString title;
    QString url;

    bool operator!=(const Content& other) const {
        return id != other.id ||
            sourceId != other.sourceId ||
            title != other.title ||
            url != other.url;
    }
};