char locked_page[] = 
"<HTML>\
	<BODY>\
		<CENTER>\
			<B>Door is locked</B>\
		</CENTER>\
		<br>\
		<CENTER>\
			<button type=\"button\" onclick= \"window.location.href='/unlocked'\">UNLOCK</button>\
		</CENTER>\
	</BODY>\
</HTML>";

char unlocked_page[] = 
"<HTML>\
	<BODY>\
		<CENTER>\
			<B>Door is unlocked</B>\
		</CENTER>\
		<br>\
		<CENTER>\
			<button type=\"button\" onclick= \"window.location.href='/locked'\">LOCK</button>\
		</CENTER>\
	</BODY>\
</HTML>";
