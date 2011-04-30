/* ------------------------------------------------------------------------ */
/*
 *   File mode constants.  These are returned from getFileMode() to indicate
 *   the mode used to open the file.  
 */

/* text mode */
#define FileModeText  1

/* "data" mode */
#define FileModeData  2

/* "raw" mode */
#define FileModeRaw   3


/*
 *   Web UI preference settings file.  This is the special file where we
 *   store display style settings for the Web UI.  
 */
#define WebUIPrefsFile         0x0002

intrinsic class File 'file/030003': Object
     *   File has no constructors.  Instead of using 'new', you create a File
     *   object by opening a file through one of the openXxxFile methods:
     *   All of the open methods have a 'filename' argument giving the name
     *   of the file to open.  This is usually a string giving a file name in
     *   the local file system.  You can also use a TemporaryFile object in
     *   place of a filename, to open a temporary file.
     *   
     *   FileCreationException - indicates that the requested file couldn't
     *   be created.  This is thrown when the access mode requires creating a
     *   new file but the named file cannot be created.
     *   FileOpenException - indicates that the requested file couldn't be
     *   FileSafetyException - the requested access mode isn't allowed for
     *   the given file due to the current file safety level set by the user.
     *   Users can set the file safety level (through command-line switches
     *   or other preference mechanisms which vary by interpreter) to
     *   restrict the types of file operations that applications are allowed
     *   to perform, in order to protect their systems from malicious
     *   programs.  This exception indicates that the user has set a safety
     *   level that is too restrictive for the requested operation.  
     *   Static creator method: open a text file.  Returns a File object that
     *   can be used to read or write the file.
     *   
     *   'filename' is the name of the file to open.  This is a string giving
     *   the name of a file in the local file system.  It can alternatively
     *   be a TemporaryFile object, to open a temporary file.
     *   
     *   'access' is the read/write mode, and must be one of FileAccessRead
     *   or FileAccessWrite.
     *   
     *   'charset' is a CharacterSet object, or can optionally be a string
     *   naming a character set, in which case a CharacterSet object for the
     *   named character set will automatically be created.  If 'charset' is
     *   omitted, the local system's default character set for file contents
     *   is used.
     *   object that can be used to read or write the file.
     *   
     *   'filename' is a string giving the file name in the local file
     *   system, or a TemporaryFile object.
     *   
     *   'access' indicates the desired read/write access and the disposition
     *   of any existing file; any of the FileAccessXxx modes can be used.
     *   
     *   When a file is opened in data mode, you can read and write integers,
     *   strings, and 'true' values to the file, and the values in the file
     *   are marked with their datatype in a private data format.  Because
     *   the file uses a tads-specific format, this mode cannot be used to
     *   read files created by other applications or write files for use by
     *   other applications; however, this storage format is convenient for
     *   storing simple data values because the File object takes care of
     *   converting to and from a portable binary format.  
     *   object that can be used to read or write the file.
     *   
     *   'filename' is a string giving the name of the file in the local file
     *   system, or a TemporaryFile object.
     *   
     *   'access' indicates the desired read/write access mode and the
     *   disposition of any existing file; any of the FileAccessXxx modes can
     *   be used.
     *   
     *   When a file is opened in raw mode, only ByteArray values can be read
     *   and written.  The File object performs no translations of the bytes
     *   read or written.  This mode requires the calling program itself to
     *   perform all data conversions to and from a raw byte format, but the
     *   benefit of this extra work is that this mode can be used to read and
     *   write files in arbitrary data formats, including formats defined by
     *   other applications.  
     *   isn't meaningful except for text files.  'charset' can be a
     *   CharacterSet object, a string giving the name of a character mapping
     *   (in which case a CharacterSet object is automatically created based
     *   on the name), or nil (in which case the local system's default
     *   character set for text files is used).  
     *   If the game is running in web server mode, the file might be on a
     *   remote storage server.  In this case, if the file was opened with
     *   write access, closing it will send the file to the storage server.
     *   
     *   Note that this method can throw an error, so you shouldn't consider
     *   updates to the file to be "safe" until this method returns
     *   successfully.  On many systems, writes are buffered in memory, so
     *   closing the file can involve flushing buffers, which can trigger the
     *   same sorts of errors that can happen with ordinary writes (running
     *   out of disk space, physical media defects, etc).  In addition, when
     *   the file is on a remote network storage server, closing a file
     *   opened with write access transmits the file to the storage server,
     *   which can encounter network errors.
     *   
     *   You should always explicitly close files when done with them.  This
     *   is especially important when writing to a file, because many systems
     *   buffer written data in memory and don't write changes to the
     *   physical media until the file is closed.  This means that updates
     *   can be lost if the program crashes (or the computer loses power,
     *   etc) while the file is still open.  Closing the file as soon as
     *   you're done with it reduces the chances of this kind of data loss.
     *   It also helps overall system performance to release resources back
     *   to the operating system as soon as you're done with them.
     *   
     *   If you *don't* close a file, though, the system will close it
     *   automatically when the File object becomes unreachable and is
     *   deleted by the garbage collector.  It's considered bad form to
     *   depend on this for the reasons above, and it's also problematic
     *   because you won't have any way of finding out if an error should
     *   happen on close.  
     *   doesn't end with a line-ending sequence, then the last line read
     *   from the file won't end in a '\n' character.  All bytes read from
     *   an error if such a conversion isn't possible), and translating the
     *   Write bytes from the given source object into the file.  This can
     *   only be used for a file opened in 'raw' mode.
     *   
     *   The source object must be one of the following object types:
     *   
     *   File: the contents of the given source file are copied to 'self'.
     *   'start' is the starting seek position in the source file; if
     *   omitted, the current seek position is the default.  'cnt' is the
     *   number of bytes to copy; if omitted, the file is copied from the
     *   given starting position to the end of the file.
     *   
     *   ByteArray: the bytes of the byte array are copied to the file.
     *   'start' is the starting index in the byte array; if omitted, the
     *   default is the first byte (index 1).  'cnt' is the number of bytes
     *   to copy; if omitted, bytes are copied from the start position to the
     *   end of the array.
    writeBytes(source, start?, cnt?);

    /*
     *   Get the file mode.  This returns one of the FileModeXxx constants,
     *   indicating the mode used to open the file (text, data, raw).  
     */
    getFileMode();

    /*
     *   Extract the file's "root name" from the given filename string.  This
     *   returns a new string giving the portion of the filename excluding
     *   any directory path.  For example, given the filename 'a/b/c.txt', if
     *   you're running on a Unix or Linux machine, the function returns
     *   'c.txt'.  Different operating systems have different conventions;
     *   this function applies the local naming rules at run time for the OS
     *   that the program is actually running on.  
     */
    static getRootName(filename);

    /*
     *   Delete the file with the given name.  This erases the file from
     *   disk.  'filename' is a string giving the name of the file to delete,
     *   or one of the special file identifier values.
     *   
     *   The file can only be deleted if the file safety level would allow
     *   you to write to the file; if not, a file safety exception is thrown.
     */
    static deleteFile(filename);

    /*
     *   Change the file mode.  'mode' is a FileModeXxx value giving the
     *   desired new file mode.
     *   
     *   If the mode is FileModeText, 'charset' is the character set mapping
     *   to use for the file; this can be given as a CharacterSet object, or
     *   as a string giving the name of a character set.  If the value is nil
     *   or the argument is omitted, the local system's default character for
     *   file contents is used.  The 'charset' parameter is ignored for other
     *   modes.
     */
    setFileMode(mode, charset?);

    /*
     *   Pack the given data values into bytes according to a format
     *   definition string, and write the packed bytes to the file.  This
     *   function is designed to simplify writing files that use structured
     *   binary formats defined by third parties, such as JPEG or PDF.  The
     *   function translates native TADS data values into selected binary
     *   formats, and writes the resulting bytes to the file, all in a single
     *   operation.
     *   
     *   'format' is the format string, and the remaining arguments are the
     *   values to be packed.
     *   
     *   Returns the number of bytes written to the file.  (More precisely,
     *   returns the final file position as a byte offset from the starting
     *   file pointer.  If a positioning code like @ or X is used in the
     *   string, it's possible that more bytes were actually written.)
     *   
     *   See Byte Packing in the System Manual for details.  
     */
    packBytes(format, ...);

    /*
     *   Read bytes and unpack into a data structure, according to the format
     *   description string 'desc'.
     *   
     *   'format' is the format string.  The function reads bytes from the
     *   current location in the file and translates them into data values
     *   according to the format string, returning a list of the unpacked
     *   values.
     *   
     *   Refer to Byte Packing in the System Manual for details.  
     */
    unpackBytes(format);

    /*
     *   Calculate the 256-bit SHA-2 hash of bytes read from the file,
     *   starting at the current seek location and continuing for the given
     *   number of bytes.  If the length is omitted, the whole rest of the
     *   file is hashed.  This has the side effect of reading the given
     *   number of bytes from the file, so it leaves the seek position set to
     *   the next byte after the bytes hashed.
     *   
     *   Returns a string of 64 hex digits giving the hash result.
     *   
     *   This can only be used on files opened in raw mode with read access.
     */
    sha256(length?);

    /*
     *   Calculate the MD5 digest of bytes read from the file, starting at
     *   the current seek location and continuing for the given number of
     *   bytes.  If the length is omitted, the whole rest of the file is
     *   digested.  This has the side effect of reading the given number of
     *   bytes from the file, so it leaves the seek position set to the next
     *   byte after the bytes digested.
     *   
     *   Returns a string of 32 hex digits giving the digest result.
     *   
     *   This can only be used on files opened in raw mode with read access. 
     */
    digestMD5(length?);

/* ------------------------------------------------------------------------ */
/*
 *   The TemporaryFile intrinsic class represents a temporary file name in
 *   the local file system.  Temporary files can be used to store data too
 *   large to conveniently store in memory.
 *   
 *   You create a temporary file with 'new TemporaryFile()'.  This
 *   automatically assigns the object a unique filename in the local file
 *   system, typically in a system directory reserved for temporary files.
 *   The local file can then be opened, read and written, and otherwise
 *   manipulated via the File class, just like any other file.  Simply pass
 *   the TemporaryFile object in place of a filename to the File.openXxx
 *   methods.  
 *   
 *   The underlying file system file will be deleted automatically when the
 *   TemporaryFile object is collected by the garbage collector (or when the
 *   program terminates).  This means that you don't have to worry about
 *   cleaning up the file system space used by the file; it'll be released
 *   automatically when the file is no longer needed.  However, you can call
 *   the deleteFile() method to explicitly release the file when you're done
 *   with it, if you want to ensure that the resource is returned to the
 *   operating system as soon as possible.
 *   
 *   TemporaryFile objects are inherently transient - they're only valid for
 *   the current session on the current local system, so they can't be saved
 *   or restored.  
 */
intrinsic class TemporaryFile 'tempfile/030000': Object
{
    /*
     *   Get the name of the underlying file system object.  This returns a
     *   string with the local filename.  This is mostly for debugging
     *   purposes or for displaying to the user.  You can't necessarily use
     *   this filename in a call to File.openXxxFile, because the file path
     *   is usually in a system directory reserved for temporary files, and
     *   the file safety level settings often prohibit opening files outside
     *   of the program's own home directory.  To open the temp file, you
     *   should always simply pass the TemporaryFile object itself in place
     *   of the filename.
     */
    getFilename();

    /*
     *   Delete the underlying file system object.  This deletes the
     *   temporary file and marks the TemporaryFile object as invalid.  After
     *   calling this, you can no longer open the file via the
     *   File.openXxxFile methods.
     *   
     *   This method allows you to release the underlying file system
     *   resources as soon as you're done with the temp file.  It's never
     *   necessary to do this.  TADS automatically deletes the underlying
     *   file system resources when the TemporaryFile object is deleted by
     *   the garbage collector (or when the program terminates), so the
     *   operating system file will be deleted eventually whether you call
     *   this method or not.  The point of this method is to let you tell the
     *   system *exactly* when you're done with the file, so that the
     *   resources can be released earlier than if we waited for garbage
     *   collection to take care of it.  This should make little difference
     *   in most situations, but in a program that will run for a long time
     *   and use a lot of temporary files, it might be worthwhile to release
     *   resources manually as soon as possible.  
     */
    deleteFile();
}


/* ------------------------------------------------------------------------ */
/*
 *   The filename passed to the File "open" methods, as well as to most
 *   system functions that accept filename arguments, can be a TadsObject
 *   object in lieu of a string.  Such an object must implement the following
 *   methods:
 *   
 *   getFilename() - return the actual filename to use, which must be a
 *   string or TemporaryFile object.
 *   
 *   closeFile() - optional.  This is called just after the underlying system
 *   file is closed, allowing the program to perform any desired
 *   post-processing on the file.  
 */
export getFilename 'FileSpec.getFilename';
export closeFile 'FileSpec.closeFile';

