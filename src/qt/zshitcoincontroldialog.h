// Copyright (c) 2017 The PIVX developers
// Copyright (c) 2017-2018 The Shitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZShitcoinCONTROLDIALOG_H
#define ZShitcoinCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "primitives/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZShitcoinControlDialog;
}

class ZShitcoinControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZShitcoinControlDialog(QWidget *parent);
    ~ZShitcoinControlDialog();

    void setModel(WalletModel* model);

    static std::list<std::string> listSelectedMints;
    static std::list<CZerocoinMint> listMints;
    static std::vector<CZerocoinMint> GetSelectedMints();

private:
    Ui::ZShitcoinControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZShitcoinCONTROLDIALOG_H
