import "./index.css";
import App from "./App";
import { createRoot } from "react-dom/client";
import React from "react";
import { SocketProvider } from "use-socket-io-react";

const SERVER_URI = import.meta.env.VITE_BASE_URL;

createRoot(document.getElementById("root")!).render(
  <React.StrictMode>
    <SocketProvider uri={SERVER_URI}>
      <App />
    </SocketProvider>
  </React.StrictMode>,
);
