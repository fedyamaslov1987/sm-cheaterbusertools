#define _ircrelay_included
#define IRC_VERSION "2.1.0"

#define BUILDD __DATE__
#define BUILDT __TIME__

/*********************************************************
 * Channel Type
 * 
 * Three different types of channels. External plugins can 
 * broadcast a message to all public/all private, or every 
 * channel that the irc relay is in.		
 *********************************************************/
enum ChannelType
{
	IRC_CHANNEL_PUBLIC = 1,
	IRC_CHANNEL_PRIVATE,
	IRC_CHANNEL_BOTH
}


/*********************************************************
 *  Called when the bot is fully connected, and ready to 
 *  send commands and stuff to the server.
 * 
 * @noreturn		
 *********************************************************/
forward OnIrcConnected();


/*********************************************************
 *  Called when someone sends a PM to the relay
 *
 * @param	String:name[]  		The name of the person who sent the pm
 * @param	String:host[]  		the host of the sender
 * @param	String:message[]  	The message that was sent
 * 
 * @noreturn		
 *********************************************************/
forward OnRelayPm();


/*********************************************************
 *  Called when someone sends a NOTICE to the relay
 * 
 * @noreturn		
 *********************************************************/
forward OnRelayNotice();


/*********************************************************
 *  Called when someone sends a normal to the relay
 * 
 * @noreturn		
 *********************************************************/
forward OnRelayMessage();


/*********************************************************
 *  Called when someone quits from the IRC server
 * 
 * @noreturn		
 *********************************************************/
forward OnUserQuit();


/*********************************************************
 *  Called after we receive a reply for host from a WHOIS command
 * 
 * @noreturn		
 *********************************************************/
forward OnWhoisHost();


// Natives to use to get variables from the core, nickname, host, message (like argv)
/*********************************************************
 *  Gets the nickname of the user who sent the message.
 * 
 * @param  String:buffer	The buffer to save the sender nickname into
 * @param  size			The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetMsgSender(String:buffer[], size);


/*********************************************************
 *  Gets the host of the user who sent the message. (ident@host)
 * 
 * @param  String:buffer	The buffer to save the senders host into
 * @param  size			The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetSenderHost(String:buffer[], size);


/*********************************************************
 *  Gets destination of the message, so we can send a message back to where it came from
 * 
 * @param  String:buffer	The buffer to save the destination into
 * @param  size			The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetMsgDestination(String:buffer[], size);


/*********************************************************
 *  Gets the message, that was sent with the server response
 * 
 * @param  String:buffer	The buffer to save the message into
 * @param  size			The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetMessage(String:buffer[], size);


/*********************************************************
 *  Gets the hostname of the nickname that you whois'd this should be used inside the OnWhoisHost forward
 * 
 *  NOTE: If the specified nickname does not exist when the whois command was issued, then the host string will be left blank
 * 
 * @param  String:buffer	The buffer to save the host into
 * @param  size			The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetWhoisHost(String:buffer[], size);


/*********************************************************
 *  Allows you to register your module, this will be used for getting info
 *  about the plugin, for re-loading etc, and listing
 *
 * @param	Handle:module	  	The handle of the module plugin
 * @param	String:name[]		The real name of the module, 
 * 					* Spaces will be removed *
 * @noreturn		
 *********************************************************/
native IRC_RegisterModule(Handle:module, const String:name[]);  // TODO: needs to work ¬¬


/*********************************************************
 *  Allows you to register your own irc command, and have
 *  it callback to a function in your plugin when it gets called
 *
 * @param	String:name[]	  	The name of the command to register
 * @param	function		The callback function in your plugin
 * @param	minAccess		The min access level a user needs to use the command (0 for disable)
 * @noreturn		
 *********************************************************/
functag IRC_Tag_CommandCallback public(argc);
native IRC_RegisterCommand(const String:name[], IRC_Tag_CommandCallback:function, const minAccess);


/*********************************************************
 *  This native will allow external plugins to send RAW 
 *  data to the server
 *
 * @param	String:command[]  	The raw data to 
 * 					send to the IRC 
 * 					server.
 * @param 	any:...			Formatting stuff
 * @noreturn		
 *********************************************************/
native IRC_SendRaw(const String:data[], any:...);


/*********************************************************
 *  This will send a simple message to a user (pm) or 
 *  to a channel
 *
 * @param	String:destination[]  	Can either be a channel name (#olly)
 * 					Or a nickname to send a PM
 * @param	String:message[]	The message to send out.
 * @param 	any:...			Formatter stuffs
 * @noreturn		
 *********************************************************/
native IRC_PrivMsg(const String:destination[], const String:message[], any:...);


/*********************************************************
 *  This will simply send a message to the same place that the triggering 
 *  command/message was sent from.
 *
 * @param	String:message[]	The message to send out.
 * @param 	any:...			Formatter stuffs
 * @noreturn		
 *********************************************************/
native IRC_ReplyMsg(const String:message[], any:...);


/*********************************************************
 *  This will send a notice back to the origin of the triggering message
 *
 * @param	String:message[]	The message to send out.
 * @param 	any:...			Formatter stuffs
 * @noreturn		
 *********************************************************/
native IRC_ReplyNotice(const String:message[], any:...);



/*********************************************************
 *  This will send a simple notice to a user (pm) or 
 *  to a channel
 *
 * @param	String:destination[]  	Can either be a channel name (#olly)
 * 					Or a nickname to send a PM
 * @param	String:message[]	The message to send out.
 * @param 	any:...			Formatter stuffs
 * @noreturn		
 *********************************************************/
native IRC_Notice(const String:destination[], const String:message[], any:...);


/*********************************************************
 *  This will show an 'action' in the specified channel, like /me [message]
 *
 * @param	String:destination[]  	Can either be a channel name (#olly)
 * 					Or a nickname to send a PM
 * @param	String:message[]	The message to send out.
 * @param 	any:...			Formatter stuffs
 * @noreturn		
 *********************************************************/
native IRC_Action(const String:destination[], const String:message[], any:...);


/*********************************************************
 *  This will send a message to all of the channels of the type specified
 *
 * @param	ChannelType:ctype  	The type of channel to send the message to
 * @param	String:message[]	The message to send out.
 * @param 	any:...			Formatter stuffs
 * @noreturn		
 *********************************************************/
native IRC_Broadcast(ChannelType:ctype, const String:message[], any:...);


/*********************************************************
 *  This will start a WHOIS command on a nickname that is connected to the server
 *  
 *  Note: add OnWhoisHost() forward, so you know when the result returns to the relay
 *
 * @param	nickname 	Nick of the person to whois
 * @noreturn		
 *********************************************************/
native IRC_Whois(const String:nickname[]);


/*********************************************************
 *  This will get the current nickname of the relay
 *
 * @param output	The buffer to store the name
 * @param size		The length of the buffer
 *********************************************************/
native IRC_GetRelayNickName(const String:output[], const size);

/*********************************************************
 *  This will check if the core is correctly connected, and ready
 *
 * @return bool	True if the core is connected, and ready for commands		
 *********************************************************/
native IRC_IsReady();


/*********************************************************
 *  Count the arguments sent along with our message
 *
 * @return count of arguments	
 *********************************************************/
native IRC_GetCmdArgc();


/*********************************************************
 *  Get the argument number specified
 * 
 * @param  num		The arguemnt number to store
 * @param  String:arg	The buffer to save the argument in
 * @param  size		The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetCmdArgv(num, String:arg[], size);


/*********************************************************
 *  Will concatonate arguments starting at the specified argument
 *  and create a string. This is usefull for lazy people who
 *  dont put stuff in " "'s
 * 
 * @param  String:arg	The buffer to save the argument in
 * @param  size		The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetCmdArgString(String:output[], size);


/*********************************************************
 *  Will return an IRC coloured version of the clients name
 * 
 * @param  client	The client index to get name for
 * @param  String:arg	The buffer to save the argument in
 * @param  size		The size of the buffer
 * @noreturn
 *********************************************************/
native IRC_GetColorName(client, String:output[], size);
stock IRC_GetColourName(client, String:output[], size) // Needs support for the REAL spelling of colour ;)
{
	IRC_GetColorName(client, output, size);
}


// Dont use these two!
forward OnGotAccessLvl(const String:dest[], p, a, lvl);
native IRC_GetAccessLevelByHost(const String:host[], const String:dest[], p, a);

// --- Plugin only stuff (not Natives)
/*****************************************************************
 * FindPlayerName
 *
 * @breif Find the userid from name or partial name
 * @params String:name name of the player to search for
 * @return -1 on not found
 *		   -2 on multiple matches
 *		   id User id of the player
 *****************************************************************/
stock FindPlayerName(const String:name[])
{
	// Get the current player count in the server
	new maxPlayers = GetMaxClients();
	new count = 0;
	new ID = -1;
	// loop through all of the player indexs
	for(new i=1;i<=maxPlayers;++i){ 
	    //make sure they are in the game
		if(IsClientConnected(i)){
			new String:PlayerName[32];
			// Get the player name
			GetClientName(i, PlayerName, 31);
			if(!strcmp(PlayerName, name, false)){++count; ID = i;}
			// Check for a match, non case sensative
			else if(StrContains(PlayerName, name, false) != -1){++count; ID = i;}	
		}
	}
	// no one found
	if(count == 0){	
		return -1;
	}else if(count > 1){ // found more than 1
		return -2;
	}else{ // we found our guy
		return ID;
	}
}


public SharedPlugin:__pl_ircrealy = 
{
	name = "irc-relay-core",
	file = "irc-relay-core.smx",
#if defined REQUIRE_PLUGIN
	required = 1,
#else
	required = 0,
#endif
};


public __pl_ircrealy_SetNTVOptional()
{
	MarkNativeAsOptional("IRC_SendRaw");
	MarkNativeAsOptional("IRC_PrivMsg");
	MarkNativeAsOptional("IRC_Notice");
	MarkNativeAsOptional("IRC_Broadcast");
	MarkNativeAsOptional("IRC_IsReady");
	MarkNativeAsOptional("IRC_RegisterCommand");
	MarkNativeAsOptional("IRC_ReplyMsg");
	MarkNativeAsOptional("IRC_ReplyNotice");
	MarkNativeAsOptional("IRC_Action");
	MarkNativeAsOptional("IRC_Whois");
	
	MarkNativeAsOptional("IRC_GetCmdArgc");
	MarkNativeAsOptional("IRC_GetCmdArgv");
	MarkNativeAsOptional("IRC_GetCmdArgString");
	MarkNativeAsOptional("IRC_GetMsgSender");
	MarkNativeAsOptional("IRC_GetSenderHost");
	MarkNativeAsOptional("IRC_GetMsgDestination");
	MarkNativeAsOptional("IRC_GetMessage");
	MarkNativeAsOptional("IRC_GetColorName");
	MarkNativeAsOptional("IRC_GetRelayNickName");
	MarkNativeAsOptional("IRC_GetWhoisHost");
}
// Yarr
