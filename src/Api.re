let fetchToken = () =>
  Js.Promise.(Http.get("https://findfalcone.herokuapp.com/token"));

let findFalcone = () => {
  let payload =
    Json.Encode.(object_([("name", string("")), ("config", string(""))]));

  Js.Promise.(Http.post("https://findfalcone.herokuapp.com/find", payload));
};