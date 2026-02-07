/*$RCSfile: KFileWrite.sql,v $: Transact-SQL script file
  $Revision: 1$ $Date: 2007-03-12 11:21:52$
  $Author: Darko Kolakovic$

  Writes a text to a file using Microsoft's isql.exe utility.
  Note: Microsoft Windows specific (Win32).
 */

-- ============================================================================
IF EXISTS (SELECT id FROM sysobjects WHERE name = 'sp_FileWrite' AND xtype = 'P')
  DROP PROC sp_FileWrite
PRINT 'Create sp_FileWrite stored procedure'
GO

/* =============================================================================
  Writes given text to a file. Requires Microsoft's isql.exe utility.
 */
CREATE PROCEDURE sp_FileWrite
  @sServer varchar(30),
  @sDB varchar(30),
  @sUser varchar(30),
  @sPWD varchar(30),
  @sOutFile varchar(255),
  @sSQL varchar(1000)
as
set nocount on
create table #trash (
out varchar(1000) null )

declare @sXP varchar(1000),
@nMaxWidth int

select  @nMaxWidth = 8000

select @sXP = 'isql' +
' -d' + @sDB +
' -U' + @sUser +
' -P' + @sPWD +
' -S' + @sServer +
' -h-1 ' +
' -w' + convert(varchar,@nMaxWidth) +
' -n' +
' -Q"' + @sSQL + '"' +
' -o' + @sOutFile

insert into #trash(out)
exec master..xp_cmdshell @sXP
go



exec xOutputToFile 'MyServer','MyDatabase','MyUser','MyPassword','c:\xx.txt','exec xHappyData'
exec master..xp_cmdshell  'type c:\xx.txt'

/*------------------------------------------------------------------------------
 *$Log: 
 * 1    Biblioteka1.0         2007-03-12 11:21:52  Darko Kolakovic 
 *$
 */
