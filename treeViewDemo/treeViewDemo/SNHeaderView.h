#ifndef SNHEADERVIEW_H
#define SNHEADERVIEW_H

#include <QHeaderView>
#include <QMouseEvent>
#include <QPainter>

class SNHeaderView : public QHeaderView
{
	Q_OBJECT

public:
	explicit SNHeaderView(QWidget *parent = 0);
	~SNHeaderView();

protected:
	virtual void paintSection(QPainter *p_painter, const QRect &p_rect, int p_nIndex) const;
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);

signals:
	void stateChanged(Qt::CheckState);

private slots:
	void slot_stateChanged(Qt::CheckState p_state);

private:
	Qt::CheckState m_state;
	bool m_bpressed;
};

#endif // SNHEADERVIEW_H
