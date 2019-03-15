

  

 
      logname = config_directory + logname;

    }

  } catch (const libconfig::SettingNotFoundException &) {}

  

  try {

    conf.lookupValue (prefix + "verbosity", verbosity);

  } catch (const libconfig::SettingNotFoundException &) {}

  

  try {

    conf.lookupValue (prefix + "lua_script", lua_script);

    if (lua_script.length () > 0 && lua_script[0database_directory = config_directory + "/data";

  param.files_directory = config_directory + "/files";

 

  td::mkdir (config_directory, CONFIG_DIRECTORY_MODE).ensure ();

}

/* }}} */

void usage () /* {{{ */ {

  std::cout 

  << "Usage: \n"

  << "  --verbosity/-v                       increase verbosity (0-ERROR 1-WARNIN 2-NOTICE 3+-DEBUG-levels)\n"

  << "  --config/-c                          config file name\n"

  << "  --profile/-p                         use specified profile\n"

  << "  --daemonize/-d                       daemon mode\n"

  << "  --logname/-L <log-name>              log file name\n"

  << "  --username/-U <user-name>            change uid after start\n"

  << "  --groupname/-G <group-name>          change gid after start\n"

  << "  --tcp-port/-P <port>                 port to listen for input commands\n"

  << "  --unix-socket/-S <socket-name>        unix socket to create\n"

  << "  --exec/-e <commands>                 make commands end exit\n"

  << "  --help/-h                            prints this help\n"

  << "  --accept-any-tcp                     accepts tcp connections from any src (only loopback by default)\n"

  << "  --bot/-b <hash>                      bot mode\n" 

  << "  --phone/-u <phone>                   specify username (would not be asked during authorization)\n"

  << "  --login                              start in login mode\n"

  ;

  exit (1);

}

/* }}} */ 

void args_parse (int argc, char *argv[]) {

  static struct option long_options[] = {

    {"verbosity", no_argument, 0, 'v'},

    {"config", required_argument, 0, 'c'},

    {"profile", required_argument, 0, 'p'},

    {"lua-script", required_argument, 0, 's'},

    {"daemonize", no_argument, 0, 'd'},

    {"logname", required_argument, 0, 'L'},

    {"username", required_argument, 0, 'U'},

    {"groupname", required_argument, 0, 'G'},

    {"tcp-port", required_argument, 0, 'P'},

    {"unix-socket", required_argument, 0, 'S'},

    {"exec", required_argument, 0, 'e'},

    {"help", no_argument, 0, 'h'},

    {"bot", required_argument, 0, 'b'},

    {"phone", required_argument, 0, 'u'},

    {"accept-any-tcp", no_argument, 0,  1001},

    {"login", no_argument, 0,  1002},

    {0,         0,                 0,  0 }

  };

  int opt = 0;

  while ((opt = getopt_long (argc, argv, "vc:p:s:dL:U:G:P:S:e:hb:u:"

  , long_options, NULL

  )) != -1) {

    switch (opt) {

    case 'v':

      verbosity ++;

      break;

    case 'c':

      config_filename = optarg;

      break;

    case 'p':

      profile = optarg;

      break;

    case 's':

      lua_script = optarg;

      break;

    case 'd':

      daemonize = true;

      break;

    case 'L':

      logname = optarg;

      break;

    case 'U':

      username = optarg;

      break;

    case 'G':

      groupname = optarg;

      break;

    case 'P':

      port = atoi (optarg);

      break;

    case 'S':

      unix_socket = optarg;

      break;

    case 'e':

      program = optarg;

      break;

    case 'h':

      usage ();

      break;

    case 'b':

      if (bot_hash.length () > 0 || phone.length () > 0) {

        std::cout << "should have at most one option of --bot and --phone\n";

        usage ();

      }

      bot_hash = optarg;

      break;

    case 'u':

      if (bot_hash.length () > 0 || phone.length () > 0) {

        std::cout << "should have at most one option of --bot and --phone\n";

        usage ();

      }

      phone = optarg;

      break;

    case 1001:

      accept_any_tcp_connections = true;

      break;

    case 1002:

      login_mode = true;

      break;

    default:

      usage ();

      break;

    }

  }

}

void termination_signal_handler (int signum) {

  td::signal_safe_write_signal_number (signum);

  #if HAVE_EXECINFO_H

  void *buffer[255];

  const int calls = backtrace (buffer, sizeof (buffer) / sizeof (void *));

  backtrace_symbols_fd (buffer, calls, 1);

  #endif 

  

  exit (EXIT_FAILURE);

}

void main_loop() {

  if (logname.length () > 0) {

    static td::FileLog file_logSignalType::Err
