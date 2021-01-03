ATTACH DATABASE 'snippet_db.db' AS 'snippet_db';

CREATE TABLE snippet_db.snippets(
    id          INTEGER         PRIMARY KEY     NOT NULL,
    author      VARCHAR(30)     NOT NULL,    
    title       TEXT(100)       NOT NULL,
    created     BIGINT          NOT NULL,
    language    VARCHAR(20)     NOT NULL,
    content     TEXT(1000)
);
