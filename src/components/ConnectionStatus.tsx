import { useSocket } from "use-socket-io-react";

const ConnectionStatus = () => {
  const { isConnected, isConnecting, isDisconnected, disconnectReason, isError, error } =
    useSocket();

  return (
    <h1 className="flex items-center gap-2 text-lg font-semibold">
      {isConnecting && "Connecting..."}
      {isConnected && (
        <>
          Connected:
          <div className="relative flex h-3 w-3">
            <div className="absolute inline-flex h-full w-full animate-ping rounded-full bg-green-400 opacity-75"></div>
            <div className="relative inline-flex h-3 w-3 rounded-full bg-green-500"></div>
          </div>
        </>
      )}
      {isDisconnected && (
        <>
          Disconnected:
          <div className="relative flex h-3 w-3">
            <div className="relative inline-flex h-3 w-3 rounded-full bg-red-500"></div>
          </div>
          {disconnectReason && <span className="text-red-500">({disconnectReason})</span>}
        </>
      )}
      {isError && (
        <>
          Error:
          <div className="relative flex h-3 w-3">
            <div className="relative inline-flex h-3 w-3 rounded-full bg-yellow-500"></div>
          </div>
          {error && <span className="text-yellow-500">({error})</span>}
        </>
      )}
    </h1>
  );
};

export default ConnectionStatus;
