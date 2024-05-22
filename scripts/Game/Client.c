//! !!!!!!!!!!!!!!!!!!!!
//! Chat commands
//! !!!!!!!!!!!!!!!!!!!!
class AdminToolingCommand : ScrServerCommand
{
	protected ScrServerCmdResult big(int playerId)
	{
		BackendApi bAPI = GetGame().GetBackendApi();
		if (!bAPI)
		{
			Debug.DPrint("Failed to get backend api");
			return ScrServerCmdResult("Failed to get backend api", EServerCmdResultType.ERR);
		}
		string pBiGuid = bAPI.GetPlayerIdentityId(playerId);
		System.ExportToClipboard(pBiGuid);
		return ScrServerCmdResult(pBiGuid, EServerCmdResultType.OK);
	}
	
	protected ScrServerCmdResult big_copy(int playerId)
	{
		BackendApi bAPI = GetGame().GetBackendApi();
		if (!bAPI)
		{
			Debug.DPrint("Failed to get backend api");
			return ScrServerCmdResult("Failed to get backend api", EServerCmdResultType.ERR);
		}
		string pBiGuid = bAPI.GetPlayerIdentityId(playerId);
		System.ExportToClipboard(pBiGuid);
		return ScrServerCmdResult("Copied to clipboard", EServerCmdResultType.OK);
	}
	
	protected ScrServerCmdResult big_show(int playerId)
	{
		BackendApi bAPI = GetGame().GetBackendApi();
		if (!bAPI)
		{
			Debug.DPrint("Failed to get backend api");
			return ScrServerCmdResult("Failed to get backend api", EServerCmdResultType.ERR);
		}
		string pBiGuid = bAPI.GetPlayerIdentityId(playerId);
		return ScrServerCmdResult(pBiGuid, EServerCmdResultType.OK);
	}
	
	protected ScrServerCmdResult help()
	{
		string str = string.Empty;
		str += "Help for bi command.";
		str += "\n#bi = Copy Your Bohemia UID and show in chat";
		str += "\n#bi show = Show Your Bohemia UID in chat";
		str += "\n#bi copy = Copy Your BohemiaU ID to clipboard";
		str += "\n#bi help = Show help for this command";
		
		return ScrServerCmdResult(str, EServerCmdResultType.OK);
	}
	
	protected ScrServerCmdResult HandleCommand(array<string> argv, int playerId = 0)
	{
		if (argv.Count() > 1)
		{
			if (argv[1] == "help")
				return help();
			if (argv[1] == "show")
				return big_show(playerId);
			if (argv[1] == "copy")
				return big_copy(playerId);
		}
		return big(playerId);
	}
	
	// Specify keyword of command
	//-----------------------------------------------------------------------------
	override string GetKeyword()
	{
		return "bi";
	}
	
	// Run command server-side
	//-----------------------------------------------------------------------------
	override bool IsServerSide()
	{
		return true;
	}
	
	// Set requirement to admin permission via RCON
	//-----------------------------------------------------------------------------
	override int RequiredRCONPermission()
	{
		return ERCONPermissions.PERMISSIONS_NONE;
	}
	
	// Set requirement to be logged in administrator for chat command
	//-----------------------------------------------------------------------------
	override int RequiredChatPermission()
	{
		return EPlayerRole.NONE;
	}
	
	// Handle Chat command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatServerExecution(array<string> argv, int playerId)
	{
		return HandleCommand(argv, playerId);
	}
	
	// Handle Chat command on client
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatClientExecution(array<string> argv, int playerId)
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
		
	}
	
	// Handle RCON command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnRCONExecution(array<string> argv)
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle successful result in OnUpdate()
	//-----------------------------------------------------------------------------
	protected ScrServerCmdResult HandleSuccessfulResult()
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle Pending command
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnUpdate()
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
}

//! EOF
