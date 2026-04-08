
extern strcpy();

char *_strerror(int errcode, char *buf)
{
	static char sbuf[] = {"error #xxx"};

	if (buf == 0)
		buf = sbuf;

	strcpy(buf, "error #xxx");
	buf[9] = errcode % 10 + '0';
	buf[8] = (errcode /= 10) % 10 + '0';
	buf[7] = (errcode / 10) % 10 + '0';

	return buf;
}

char *strerror(int code)
{
	return _strerror(code, 0);
}
