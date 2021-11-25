all:
	cc -o macapp macapp.c
clean:
	rm -f macapp
install:
	install -m 755 macapp /usr/local/bin
	install -m 644 macapp.service /etc/systemd/system/
	systemctl daemon-reload
uninstall:
	rm -f /usr/local/bin/macapp
	rm -f /etc/systemd/system/macapp.service
	systemctl daemon-reload
