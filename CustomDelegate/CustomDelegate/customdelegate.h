#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include "ui_customdelegate.h"

/// <����ѡ���TABLE-HEADER>
class TableHeaderView
	: public QHeaderView
{
	Q_OBJECT

public:
	TableHeaderView(Qt::Orientation orientation, QWidget *parent = 0);

public:
	/// <����ĳ��checked>
	void SetCheckCol(quint32 ncol);

protected:
	/// <���Ƹ�ѡ��>
	virtual void paintSection(QPainter *painter, const QRect &rect, int index) const;

	/// <��갴�±�ͷ>
	virtual void mousePressEvent(QMouseEvent *event);

	/// <���ӱ�ͷ�ͷţ������źţ�����model����>
	virtual void mouseReleaseEvent(QMouseEvent *event);

	/// <��껬�����뿪�����¸�ѡ��״̬>
	virtual bool event(QEvent *event);

signals:
	void Signal_StateChanged(Qt::CheckState);

private:
	bool mPressed;
	bool mChecked;
	bool mTristate;
	bool mNoChange;
	bool mMoving;
	quint32 mCheckCol;
};


class CustomDelegate : public QMainWindow
{
	Q_OBJECT

public:
	CustomDelegate(QWidget *parent = 0);
	~CustomDelegate();

private:
	Ui::CustomDelegateClass ui;
};

#endif // CUSTOMDELEGATE_H
