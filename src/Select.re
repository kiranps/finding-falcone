[@bs.val] external setTimeout: (unit => unit, int) => unit = "setTimeout";

module Input = {
  [@react.component]
  let make = (~value, ~onBlur, ~onClick, ~onChange) =>
    <input
      value
      onClick
      onBlur
      onChange
      type_="text"
      placeholder="select"
      className="bg-red-100 outline-none w-full cursor-pointer focus:cursor-text"
    />;
};

module Menu = {
  module Item = {
    [@react.component]
    let make = (~value, ~onClick) =>
      <div className="cursor-pointer hover:bg-blue-300" onClick>
        {React.string(value)}
      </div>;
  };

  [@react.component]
  let make = (~children, ~hide) =>
    hide
      ? <div className="absolute bg-green-200 w-full z-10"> children </div>
      : React.null;
};

module Box = {
  [@react.component]
  let make = (~children) =>
    <div className="inline-block relative bg-green-100 w-40"> children </div>;
};
module Container = {
  [@react.component]
  let make = (~children) => <div className="block w-full"> children </div>;
};

[@react.component]
let make = (~values: list(string), ~onChange) => {
  let (active, toggleActive) = React.useState(_ => false);
  let (value, changeValue) = React.useState(_ => "");

  let handleClick = _e => {
    toggleActive(active => !active);
    changeValue(value => active ? value : "");
  };

  let handleChange = e => {
    ReactEvent.Form.target(e)##value |> changeValue;
  };

  /*
    setTimeout is for avoiding clash btw onBlur and onClick
    onBlur remove Menu from dom on which onClick is register
    thus preventing onClick beign triggered
   */
  let handleBlur = _e => {
    setTimeout(() => toggleActive(_ => false), 200);
  };

  let handleSelect = value => {
    changeValue(_ => value);
    onChange(value);
  };

  <Box>
    <Container>
      <Input
        value
        onBlur=handleBlur
        onClick=handleClick
        onChange=handleChange
      />
      <Menu hide=active>
        {values
         |> List.filter(Js.String.startsWith(value))
         |> List.mapi((i, x) =>
              <Menu.Item
                key={string_of_int(i)}
                value=x
                onClick={_e => handleSelect(x)}
              />
            )
         |> Array.of_list
         |> React.array}
      </Menu>
    </Container>
  </Box>;
};