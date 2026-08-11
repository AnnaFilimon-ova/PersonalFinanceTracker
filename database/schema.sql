PRAGMA foreign_keys = ON;

CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    email TEXT UNIQUE,
    password_hash TEXT NOT NULL
);

CREATE TABLE categories (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    type TEXT NOT NULL CHECK (type IN ('expense', 'income'))
);

CREATE TABLE expenses (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    category_id INTEGER NOT NULL,
    amount REAL NOT NULL CHECK (amount > 0),
    date TEXT NOT NULL DEFAULT CURRENT_DATE,

    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (category_id) REFERENCES categories(id)
);

CREATE TABLE incomes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    category_id INTEGER NOT NULL,
    amount REAL NOT NULL CHECK (amount > 0),
    date TEXT NOT NULL DEFAULT CURRENT_DATE,

    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (category_id) REFERENCES categories(id)
);

INSERT INTO categories (name, type) VALUES
    ('Transport', 'expense'),
    ('Shopping', 'expense'),
    ('Education', 'expense'),
    ('Pets', 'expense'),
    ('Beauty', 'expense'),
    ('Gas', 'expense'),
    ('Food', 'expense'),
    ('Electronics', 'expense'),
    ('Health', 'expense'),
    ('Kids', 'expense'),
    ('Travel', 'expense'),
    ('Internet', 'expense'),
    ('Salary', 'income'),
    ('Freelancing', 'income'),
    ('Business', 'income'),
    ('Investments', 'income'),
    ('Transfers', 'income'),
    ('Scholarship', 'income'),
    ('Refund', 'income'),
    ('Other', 'income');