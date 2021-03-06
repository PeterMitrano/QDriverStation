/*
 * Copyright (c) 2015 WinT 3794 <http://wint3794.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _QDS_MW_CONSOLE_H
#define _QDS_MW_CONSOLE_H

#include <QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QPlainTextEdit;

class Console : public QWidget
{
    Q_OBJECT

public:
    explicit Console (QWidget* parent);

private slots:
    void createWidgets();
    void createLayouts();
    void configureStyles();

    void copy();
    void clear();
    void log (QString message);

private:
    QVBoxLayout* m_mainLayout;
    QHBoxLayout* m_buttonsLayout;

    QPlainTextEdit* m_console;

    QWidget* m_buttonsWidget;
    QPushButton* m_copyButton;
    QPushButton* m_clearButton;
};

#endif
