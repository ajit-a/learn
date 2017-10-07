#ifndef __SERVER_H_
#ifdef __SERVER_H_

class ORDER
{
	private:
		int sid;
		float price;
		int qty;
};
class QUEUE
{
	private:
		ORDER o;
	public:
};
class STOCK
{
	private:
		int sid;
		QUEUE offerQ;
		QUEUE bidQ;
};
#endif
